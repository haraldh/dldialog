/*-*- c++ -*-******************************************************************
**
**  Copyright (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
**  $Id: dldialog.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
******************************************************************************/
#include <ansidecl.h>
#include <ctype.h>
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <iostream.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fstream>
#include <strstream>
#include <dlfcn.h>
#include <locale.h>
#include "dld_gui.h"
#include "dld_lib.h"

#include "dldialog.h"
#include "dld_parser.h"

extern char **environ;

T_DLD_MODE DLD_Mode = DLD_NONE;
int fd_out, fd_in, fd_err, sock_in;
struct  sockaddr_un  sock_addr;
socklen_t sock_len;
DLD_Gui *DLD_GUI;
int DLD_Debug = 0;
string inpath; 
string indir; 
fstream DLDout;
ofstream DLDdbg;
ofstream DLDerr;

char *my_ttyname = NULL;

char dld_title[1024];

static const char *infifo; 

int tty_fdout, tty_fdin, tty_fderr;

DLD_Gui * (*func_dld_lib_init) (const char *name,
				       int argc, char **argv);

static   char *tname  /*, *lname */ ;

/** Prints the Usage of dldialog.
 *  @param name argv[0]
 */
void
print_usage ( const char *name )
{
    cerr << _("Usage: ") << name << _(" [OPTIONS]\n"
	    "\nOPTIONS:\n"
	    "\t-f, --file \tread input from file, rather than from stdin\n")
#ifdef HAVE_QT
	 << _("\t-q, --qt \tstart with Qt (X11) interface\n")
#endif
#ifdef HAVE_TVISION
	 << _("\t-t, --tv \tstart with tvision (terminal) interface\n")
#endif
	 << _("\t-T, --title \tsets the window title to the next argument\n"
	      "\t-p, --parse \tparse only to check input\n"
	      "\t-b, --start \tstart dldialog server\n"
	      "\t-e, --stop \tstop dldialog server\n"
	      "\t-w, --wait \twait for dldialog server to end\n"
	      "\t-d, --debug \tdisplays debugging output\n"
	      "\t-v, --version \tdisplay version information and exit\n"
	      "\t-h, --help \tdisplay this help and exit\n"
	      "\n");
}

char *
dld_mytty ()
{
   static CONST char dev[] = "/dev";
   static char *name = NULL;
   static size_t namelen = 0;
   struct stat st;
   dev_t mydev = 0;

   /*
    * ino_t myino;
    */
   DIR *dirstream;
   struct dirent *d;
   int save = errno;
   int d_namlen;
   FILE *statfile;

   if ((statfile = fopen ("/proc/self/stat", "r")) != NULL) {
      int dev;

      fscanf (statfile, "%*d %*s %*c %*d %*d %*d %d", &dev);
      fclose (statfile);
      mydev = dev;
   }

   dirstream = opendir (dev);

   if (dirstream == NULL)
      return NULL;

   while ((d = readdir (dirstream)) != NULL) {
      d_namlen = strlen (d->d_name) + 1;
      if (sizeof (dev) + d_namlen > namelen) {
	 if (name)
	    free (name);
	 namelen = (sizeof (dev) + d_namlen) << 1;	/*
							 * * * * Big enough.  
							 */
	 name = (char *) malloc (namelen);
	 if (!name)
	    return NULL;
	 (void) memcpy (name, dev, sizeof (dev) - 1);
	 name[sizeof (dev) - 1] = '/';
      }
      (void) memcpy (&name[sizeof (dev)], d->d_name,
		     d_namlen);
      if ((stat (name, &st) == 0)
	  && ((unsigned) st.st_ino == (unsigned) d->d_ino)
	  && S_ISCHR (st.st_mode)
	  && st.st_rdev == mydev) {
	 (void) closedir (dirstream);
	 my_ttyname = name;
	 errno = save;
	 return name;
      }
   }

   (void) closedir (dirstream);
   errno = save;
   return NULL;
}
void fill_sock(socklen_t *len, struct sockaddr_un *ctladdr, const char *path)
{
  // Fill sockaddr
   bzero((char *)ctladdr, sizeof(ctladdr));
   ctladdr->sun_family = AF_UNIX;
   strcpy(ctladdr->sun_path, path);
   *len = sizeof(ctladdr->sun_family) + strlen(path);
}

void dld_make_fifo(int pid)
{
   char *ttyp = strrchr(tname, '/');
   if(!ttyp)
      ttyp = tname;
   else
      ttyp++;


   {
     char path[PATH_MAX];
     snprintf(path, PATH_MAX, DLD_SOCKET_DIR "_%s_%d", ttyp, pid); 
     indir = path;
	  mkdir(indir.c_str(), S_IRWXU);
   }

   {
     char path[PATH_MAX];
     snprintf(path, PATH_MAX, "%s/dld_in_%d", indir.c_str(), pid);
	  inpath = path;
   }

   // Create UNIX socket
   sock_in = socket(AF_UNIX, SOCK_STREAM, 0);

   // Fill sockaddr
   fill_sock(&sock_len, &sock_addr, inpath.c_str());

   // Remove evtl. old stale file
   unlink (inpath.c_str());   
   
   // bind a socket to that address
   if ( bind(sock_in, (struct sockaddr *)(&sock_addr), sock_len) == -1) {
      perror("dld_server: bind");
      cerr << inpath << " used" << endl;
      exit(1);
   }
   
   if ( listen(sock_in, 10) == -1) {
      perror("dld_server: listen");
      exit(1);
   }


   setenv("DLDIALOG_INFIFO", inpath.c_str(), true);

   infifo = inpath.c_str();
}

void dld_cleanup(int)
{
   unlink(infifo);
   
   char *ttyp = strrchr(tname, '/');
   if(!ttyp)
      ttyp = tname;
   else
      ttyp++;
   
   rmdir(indir.c_str());
}


int
dld_main (int argc, char **argv, int pipe_fd)
{
   int ret = 0;

   if(!strlen(dld_title))
      strcpy(dld_title, "DLDialog");

   signal(SIGINT, dld_cleanup); 
   signal(SIGTERM, dld_cleanup); 
   signal(SIGKILL, dld_cleanup); 
   signal(SIGQUIT, dld_cleanup); 

   if (func_dld_lib_init && 
     (DLD_GUI = (*func_dld_lib_init) (dld_title, argc, argv)) != 0) {
      
      /* Give the waiting client a shot */
      {
	 ofstream pipeout(pipe_fd);
	 pipeout << "ready!;" << endl << flush;
	 pipeout.close();
      }

#ifdef DEBUG
      /* Parse it */
      try {
#endif
	 ret = dld_parse ();
	 DLDdbg.flush ();
	 DLDerr.flush ();
	 DLDout.flush ();
#ifdef DEBUG
      }
      catch (DLD_Parse_Error) {
      }
      catch (DLD_Pipe_Error) {
      }
      catch (Bad_arg& err) {
	 DLDerr << err.file << ":" << err.line << ": " 
		<< err.reason << endl 
		<< flush;
	 
	 if(DLD_GUI) {
	    delete DLD_GUI;
	    DLD_GUI = 0;
	 }
      }
#endif

      if(DLD_GUI) {
	 delete DLD_GUI;
	 DLD_GUI = 0;
      }	 

      if(DLD_run == 0 && DLDout.is_open()) {      
	 // For the last dldialog --end
	 DLDout << "all_ok;" << endl << flush;
//	 DLDout.close();
      }
      dld_cleanup(0);
   }
   return ret;
}

void dld_start()
{
   // Create UNIX socket
   sock_in = socket(AF_UNIX, SOCK_STREAM, 0);
   
   // Fill sockaddr
   fill_sock(&sock_len, &sock_addr, infifo);

   if (connect(sock_in, (struct sockaddr *)&sock_addr, sock_len) == -1 ) {
      perror("dld_client_start: connect");
      cerr << infifo << _(" tried!") << endl;
      exit(1);
   }

   fstream com(sock_in);

#ifdef DEBUG
   if(DLD_Debug)
      cerr << _("Sending start") << endl;
#endif
   com << "dld_start;" << endl << flush;

   string dummy;
#ifdef DEBUG
   if(DLD_Debug)
      cerr << _("Waiting for ok") << endl;
#endif

   while(com >> dummy && dummy != "ok;");

   com.close();
}

void dld_stop()
{
   // Create UNIX socket
   sock_in = socket(AF_UNIX, SOCK_STREAM, 0);
   
   // Fill sockaddr
   fill_sock(&sock_len, &sock_addr, infifo);

   if (connect(sock_in, (struct sockaddr *)&sock_addr, sock_len) == -1 ) {
      perror("dld_client_stop: connect");
      cerr << infifo << " tried!" << endl;
      exit(1);
   }

   fstream com(sock_in);

#ifdef DEBUG
   if(DLD_Debug)
      cerr << _("Sending stop") << endl;
#endif
   com << "dld_stop;" << endl;

   string dummy;
#ifdef DEBUG
   if(DLD_Debug)
      cerr << _("Waiting for ok") << endl;
#endif
   while((com >> dummy) && (dummy != "ok;") && (dummy != "all_ok;") );

   if(dummy == "all_ok;") {
      while(com >> dummy);      
   }
   com.close();
}

bool dld_send()
{
   signal(SIGPIPE, SIG_IGN);
   // Create UNIX socket
   sock_in = socket(AF_UNIX, SOCK_STREAM, 0);
   
   // Fill sockaddr
   fill_sock(&sock_len, &sock_addr, infifo);

   if (connect(sock_in, (struct sockaddr *)&sock_addr, sock_len) == -1 ) {
      perror("dld_client_send: connect");
      cerr << infifo << _(" tried!") << endl;
      exit(1);
   }

   fstream com(sock_in);

#ifdef DEBUG
   if(DLD_Debug)
      cerr << _("Sending client {") << endl;
#endif
   com << "dld_client {" << endl << flush;
   
   for(int i=0; environ[i] != 0; i++) {
      char *div = strchr(environ[i], '=');
      if(div) {
	 char *olddiv = div;
	 *div = 0;
	 div++;
	 com << environ[i] << "=\"";
	 char *esc;
	 while((esc = strchr(div, '\"'))!=0) {
	    *esc = 0;
	    com << div << "\\\"";
	    div = esc+1;
	 }
	 com << div << "\";" << endl;
	 *olddiv = '=';
      }
   }

   com << "dld_env_end;" << endl;
   

   com << cin.rdbuf();

   char buf[YYLMAX];      
/*
   int len;
   while((len = read(STDIN_FILENO, buf, YYLMAX-1)) && (len > 0)) {
      buf[len] = 0;
      com << buf << flush;
   }
*/

#ifdef DEBUG   
   if(DLD_Debug)
      cerr << _("Sending }") << endl;
#endif
   com << '}' << endl << flush;
      
   while(com.getline(buf, 1025) && (strlen(buf) == 0));

   if(!com)
      return false;

   com.close();

   if(strstr(buf, "error;"))
      return false;
      
#ifdef DEBUG   
   if(DLD_Debug)
      cerr << _("Getting output pipe") << endl;
#endif
   {
      struct stat s_buf;
      if(stat(buf, &s_buf) == -1) {
	 cerr << buf << _(" is no output pipe") << endl;
	 exit(1);
      }
   }
   
#ifdef DEBUG   
   if(DLD_Debug)
      cerr << _("Opening output pipe ") << buf << endl;
#endif
   string pipepath(buf);
   ifstream in(buf);
   
#ifdef DEBUG   
   if(DLD_Debug)
      cerr << _("Reading output pipe ") << buf << endl << flush;
#endif

   cout << in.rdbuf();
   
#ifdef DEBUG   
   if(DLD_Debug)
      cerr << _("Deleting output pipe ") << buf << endl;
#endif
   unlink(pipepath.c_str());

   signal(SIGPIPE, SIG_DFL);

   return true;
}

int
dld_server (int argc, char **argv)
{
//   int box;
   int c;
   int curopt;
   bool startflag = false;

   string dl_dlpath = "libdld_gen.so";

   if (argc > 1) {
      while (1) {
	 int oi = 0;

	 static struct option long_options[] =
	 {
	    {"generic", 0, 0, 'g'},
	    {"qt", 0, 0, 'q'},
	    {"tv", 0, 0, 't'},
	    {"title", 1, 0, 'T'},
	    {"debug", 0, 0, 'd'},
	    {"parse", 0, 0, 'p'},
	    {"reloaded", 0, 0, 'r'},
	    {"file", 1, 0, 'f'},
	    {"help", 0, 0, 'h'},
	    {"version", 0, 0, 'v'},
	    {"start", 0, 0, 'b'},
	    {"stop", 0, 0, 'e'},
	    {0, 0, 0, 0}
	 };


	 c = getopt_long (argc, argv, "begqtpdf:vhrT:", long_options, &oi);
	 if (c == -1)
	    break;

	 curopt = (optind - 1) ? optind -1 : 1; 
	 
	 switch (c) {
	 case 'h':
	    print_usage (argv[0]);
	    return (0);
	    break;

	 case 'v':
	    cout << _("dldialog version ") << VERSION << endl
                 << _("\tby Harald Hoyer (dldialog@parzelle.de)\n"
		      "\tCopyright (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -");
	    return (0);
	    break;

	 case 'g':
	    if (DLD_Mode == DLD_NONE) {
	       char *pre;
	       char *c;
	       
	       for(c = argv[curopt]; (c && *c); c++)
		  if(*c == 'g')
		  {
		     *c = 'r';
		     break;
		  }
	       pre = getenv ("DLD_PRELOAD");
	       if (pre) {
		  setenv ("LD_PRELOAD", pre, 1);
	       }
	       else {
		  cerr << _("DLD_PRELOAD not specified!") << endl;
	       }
	       DLD_Mode = DLD_GENERIC;
	    }
	    break;

	 case 'q':
#ifdef HAVE_QT
	    if (DLD_Mode == DLD_NONE) {
	       dl_dlpath = "libdld_qt.so";
	       DLD_Mode = DLD_QT;
	    }
	    else {
	       cerr << _("Another mode was already selected!") << endl;
	    }
#else
	    cerr << _("QT support not compiled in!") << endl;
#endif
	    break;

	 case 't':
#ifdef HAVE_TVISION
	    if (DLD_Mode == DLD_NONE) {
	       /*
		* Lets be the master of the session.
		* Good for the console.
		*/
	       dl_dlpath = "libdld_tv.so";
	       DLD_Mode = DLD_TV;
	    }
	    else {
	       cerr << _("Another mode was already selected!") << endl;
	    }
#else
	    cerr << _("TVision support not compiled in!") << endl;
#endif
	    break;

	 case 'p':
	    if (DLD_Mode == DLD_NONE) {
	       dl_dlpath = "libdld_gen.so";
	       DLD_Mode = DLD_PARSE;
	    }
	    else {
	       cerr << _("Another mode was already selected!") << endl;
	    }
	    break;

	 case 'd':
	    DLD_Debug = 1;
	    break;

	 case 'f':
	    if(freopen (optarg, "rb", stdin)==0) {
	       perror(optarg);
	       return (1);
	    }
	    break;

	 case 'T':
	    strncpy(dld_title, optarg, sizeof(dld_title)-1);
	    break;

	 case 'b':
	    startflag = true;
	    break;

	 default:
	    cout << _("Try `") << argv[0] << " --help'." << endl;
	    return (1);
	 }
      }
   }

   if (!(tname = ttyname (STDERR_FILENO))) {
      tname = dld_mytty ();
      if(!tname) {
	 tname = "no_tty";
      }
   }

   int pipe_fd[2];
   pipe(pipe_fd);

   int pid;
   if ((pid = fork ()) == 0) {

      close(pipe_fd[0]);

      pid = getpid();

      struct rlimit RLP;
      getrlimit (RLIMIT_OFILE, &RLP);
  
      for (int i = 3; i < RLP.rlim_cur; i++)
	 if(i != pipe_fd[1]) 
	    close (i);	       
      
      dld_make_fifo(pid);
      
      if(DLD_Mode == DLD_NONE) {
#ifdef HAVE_TVISION
	 DLD_Mode = DLD_TV;
	 dl_dlpath = "libdld_tv.so";
#else
	 DLD_Mode = DLD_PARSE;
	 dl_dlpath = "libdld_gen.so";
#endif
      }      

      fd_err = dup (STDERR_FILENO);
      
      DLDerr.attach (fd_err);

      if(DLD_Mode == DLD_TV) {
	 if(!tname) {
	    DLDerr << "No terminal!" << endl << flush;
	    return(10);	    
	 }

	 setsid();   
	 tty_fderr = open(tname, O_WRONLY);
	 
	 if (!isatty (STDIN_FILENO)) {
	    tty_fdin = open (tname, O_RDONLY);
	 }
	 else {
	    tty_fdin = STDIN_FILENO;
	 }
	 
	 if (!isatty (STDOUT_FILENO)) {
	    //     tty_fdout = open (tname, O_WRONLY);       
	    tty_fdout = open(tname, O_WRONLY);
	 }
	 else {
	    tty_fdout = STDOUT_FILENO;
	 }
      } else {
	 if(tname) {
	    tty_fdin = open (tname, O_RDONLY);
	    tty_fdout = open(tname, O_WRONLY);
	 }
	 else
	 {
	    dup2(STDIN_FILENO, tty_fdin);
	    dup2(STDOUT_FILENO, tty_fdout);
	 }
//	 close(STDERR_FILENO);
	 close(STDIN_FILENO);
	 close(STDOUT_FILENO);
      }

      if (DLD_Debug) {
	 DLDdbg.attach (fd_err);
      }
      else {
	 DLDdbg.open ("/dev/null");
      }

      // Open our library
      void *dl_handle = dlopen(dl_dlpath.c_str(), RTLD_NOW);
      
      if(!dl_handle) {
	 DLDerr << "dlopen(" << dl_dlpath << "): ";
	 DLDerr << dlerror() << endl;
	 abort();
      }
      
      // Get the entry function
      func_dld_lib_init = (DLD_Gui *(*)(const char *name, 
					int argc, 
					char **argv))
	 dlsym(dl_handle, "dld_lib_init");
      
      const char *error = 0;
      
      if ((error = dlerror()) != NULL)  {
	 DLDerr << "dlsym: ";
	 DLDerr << error << endl;
	 abort();
      }
      
      // Go for the main loop
      dld_main(argc, argv, pipe_fd[1]);

      
/* IT IS NOT SAFE TO CLOSE THE LIBRARY DUE TO STATIC OBJECTS in tvision
 * and a bug in egcs and libdl ....
#ifdef DEBUG
      DLDdbg << "Closing library!" << endl << flush;
#endif
      
      dlclose(dl_handle);

      if ((error = dlerror()) != NULL)  {
	 DLDerr << "dlsym: ";
	 DLDerr << error << endl << flush;
	 abort();
      }
*/     
            
   }
   else /* fork */
   {

      close(pipe_fd[1]);

      char *ttyp = strrchr(tname, '/');
      if(!ttyp)
	 ttyp = tname;
      else ttyp++;

      {
		  char path[PATH_MAX];
		  snprintf(path, PATH_MAX, DLD_SOCKET_DIR "_%s_%d/dld_in_%d", ttyp, pid, pid);
		  inpath = path;
      }

      setenv("DLDIALOG_INFIFO", inpath.c_str(), true);
            
      infifo = inpath.c_str();
      
      {
	 char buf[1025];      
	 ifstream ready(pipe_fd[0]);
	 ready.getline(buf, 1025);
      }
      close(pipe_fd[0]);
      /*
       * We are the first client
       * Give it a first shot so that an end is needed
       */
      dld_start();

      if(!startflag) {
	 // Ok ... there was no --start
	 if(dld_send())
	   dld_stop();

	 int status;
	 // Just wait for our small child to exit
	 waitpid(pid, &status, 0);
      }
      else {
	 // Give that thing to the outer world
	 cout << "DLDIALOG_INFIFO=\"" << infifo <<  "\";" << endl;
      }

   }	       
   
   return 0;
}

int
dld_client (int argc, char **argv)
{
   int c;
   int curopt;
	    
   if (argc > 1) {
      while (1) {
	 int oi = 0;

	 static struct option long_options[] =
	 {
	    {"generic", 0, 0, 'g'},
	    {"qt", 0, 0, 'q'},
	    {"tv", 0, 0, 't'},
	    {"title", 1, 0, 'T'},
	    {"debug", 0, 0, 'd'},
	    {"file", 1, 0, 'f'},
	    {"help", 0, 0, 'h'},
	    {"version", 0, 0, 'v'},
	    {"start", 0, 0, 'b'},
	    {"stop", 0, 0, 'e'},
	    {"wait", 0, 0, 'w'},
	    {0, 0, 0, 0}
	 };


	 c = getopt_long (argc, argv, "gqtTdpf:vbew", long_options, &oi);
	 if (c == -1)
	    break;

	 curopt = (optind - 1) ? optind -1 : 1; 
	 
	 switch (c) {
	 case 'h':
	    print_usage (argv[0]);
	    return (0);
	    break;

	 case 'v':
	    cout << _("dldialog version ") << DLD_VERSION_STRING << endl
                 << _("\tby Harald Hoyer (dldialog@parzelle.de)\n" 
		      "\tCopyright (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -\n");
	    return (0);
	    break;

	 case 'd':
	    DLD_Debug = 1;
	    break;

	 case 'f':
	    if(freopen (optarg, "rb", stdin) == 0) {
	       perror(optarg);
	       return(1);
	    }
	    break;

	 case 'b':
	 {	    
	    dld_start();
            cout << "DLDIALOG_INFIFO=\"" << infifo <<  "\";" << endl;
	    return 0;
	    break;
	 }
	 case 'e':
	 {
            dld_stop();
	    return 0;
	    break;
	 }
	 case 'w':
	 {
	    dld_stop();
            struct stat s_buf;
               
            // Scan for infifo
            while(stat(infifo, &s_buf) != -1)
               usleep(20000);

            return 0;
	    break;
	 }
	 case 'q':
	 case 't':
	 case 'g':
	    break;
	 default:
	    cout << _("Try `") << argv[0] << "' --help'." << endl;
	    return (1);
	 }
      }
   }

   dld_start();

   if(dld_send())
      dld_stop();
   else return 1;

   return 0;
}

int
main (int argc, char **argv)
{   
   setlocale (LC_ALL, "");
//   setlocale (LC_MESSAGES, "");
//   setlocale (LC_NUMERIC, "");
   bindtextdomain (PACKAGE"-scripts", LOCALEDIR);
   bindtextdomain (PACKAGE, LOCALEDIR);
   textdomain (PACKAGE);

   infifo = getenv("DLDIALOG_INFIFO");

   if(infifo)
     return dld_client(argc, argv);
   else
     return dld_server(argc, argv);
}

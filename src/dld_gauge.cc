#include "dld_gauge.h"
#include "dld_parser.h"
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

extern char **environ;
DLD_Gauge::~DLD_Gauge()
{
   in.close();
   if(gaugefd) {      
      if(dialog)
	 dialog->deregister_gauge(this, gaugefd);
/*      DLD_run--;
      DLDdbg << "--DLD_run = " << DLD_run << endl << flush;
*/
      kill(execpid, SIGTERM);
   }
}

void DLD_Gauge::create()
{
   if(gaugestr.length()) {
#ifdef DEBUG
      DLDdbg << "gauge  exec " << gaugestr << endl << flush;
#endif
      int pid;
      int fd[2];
      pipe (fd);
      
      if ((pid = fork ()) == 0) {
	 char *argv[4];
	 int i;

	 dialog->set_up_environment();

	 dup2 (fd[1], STDOUT_FILENO);

	 char exec[gaugestr.length()+1];
	 strcpy (exec, gaugestr.c_str());

	 for (i = 4; i < 256; i++)
	    close (i);

	 exit(system(exec));
      }
/*      DLD_run++;
      DLDdbg << "++DLD_run = " << DLD_run << endl << flush;
*/
      close (fd[1]);
      gaugefd = fd[0];
      in.attach(gaugefd);
      execpid = pid;
      dialog->register_gauge(this, gaugefd);
   }
}

void DLD_Gauge::parse() 
{
   if(!gaugefd)
      return;
   else {
      double pro=0.0;
      string buf;   
//   char c;
      
      fcntl(gaugefd, F_SETFL, O_RDONLY|O_NONBLOCK);
      
      while(in >> buf) {
	 if(sscanf(buf.c_str(), " %lf", &pro))
	    set_progress((int)pro);
      }
      
      fcntl(gaugefd, F_SETFL, O_RDONLY);
      
      in.clear();
      
      int status;
      int exitstatus=0;
      pid_t pid = waitpid(execpid, &status, WNOHANG);
      if( pid != 0 )
      {
	 if(pid > 0 && WIFEXITED(status)) {
	    exitstatus = WEXITSTATUS(status);
	    DLDdbg << "Gauge exited with " << exitstatus << endl << flush;
	 }
	 else if (pid > 0 && WIFSIGNALED(status)) {
	    exitstatus = WTERMSIG(status);
	    DLDdbg << "Gauge killed with signal " << exitstatus << endl << flush;
	 }
	 in.close();
	 dialog->deregister_gauge(this, gaugefd);
	 set_progress(-exitstatus-1);
	 gaugefd = 0;      
/*	 DLD_run--;
	 DLDdbg << "--DLD_run = " << DLD_run << endl << flush;
*/
      }
   }
}


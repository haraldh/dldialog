/******************************************************************************
**
** $Id: dld_gui.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
/*
#include "dld_parser.h"
#include "dldialog.h"
*/
#include "dld_lib.h"
#include "dld_parser.h"
#include "dldialog.h"
#include "dld_gui.h"
#include "dld_gauge.h"

extern char **environ;

 void DLD_Gui::
set_env (const string& _name, const string& _value) 
{
   envmap[_name] = convstr(_value);
}

 string DLD_Gui::
get_env (const string& _name) 
{
   return envmap[_name];
}

 void DLD_Gui::
clear_env() 
{
   envmap.erase(envmap.begin(), envmap.end());
}

 bool DLD_Gui::
parse(long wait)
{
//   static int infd = 0;
   
   if(!DLD_error) {
      int fd_max=-1;
      fd_set fdset;
            
      FD_ZERO(&fdset);    

      // Lets wait for incoming sockets
      FD_SET(sock_in, &fdset);
      fd_max = max(fd_max, sock_in);
     
      // Scan all gauge execs
      for(map<int, DLD_Gauge_Ptr>::iterator i = gaugemap.begin();
	  i != gaugemap.end(); ++i) {
	 FD_SET(i->first, &fdset);
	 fd_max = max(fd_max, i->first);
      }

      struct timeval timeout = {wait/1000000, wait%1000000};
      
      if(fd_max != -1 && select(fd_max+1, &fdset, 0, 0, (wait < 0) ? NULL : &timeout) > 0) {
//      if(fd_max != -1 && select(fd_max+1, &fdset, 0, 0, NULL) > 0) {
	 // Look if there are gauges to update...
	 for(map<int, DLD_Gauge_Ptr>::iterator i = gaugemap.begin();
	     i != gaugemap.end(); ++i) {
	    if(FD_ISSET(i->first, &fdset)) {
	       if (i->second)
		  i->second->parse();
	    }
	 }

	 if(FD_ISSET(sock_in, &fdset) && DLD_run >= 0) {
	    socklen_t len = sock_len;
	    int fd_in = accept(sock_in, (struct sockaddr *)&sock_addr, &len);
//	 fcntl(fd_in, F_SETFL, O_NONBLOCK);
	    if(DLDout.is_open())
	       DLDout.close();
	    DLDout.attach (dup(fd_in));

	    if(!yyin)
	       yyin = fdopen(fd_in, "rwb");
	 	    
	    yyparse ();
	    DLDout << flush;
	    close(fd_in);
	    if(DLD_run >= 0 && DLDout.is_open())
	       DLDout.close();
	 }
      }
   }
   
   int status;
   pid_t pid;
   do {
      pid = waitpid(-1, &status, WNOHANG);
      if (pid > 0) {
	 DLDdbg << "child " << pid << " exited." << endl << flush;
	 map<int, DLD_Gauge_Ptr>::iterator i;
	 for(i = gaugemap.begin(); i != gaugemap.end(); ++i) {
	    if(pid == i->second->execpid)
	       break;
	 }
	 if(i == gaugemap.end()) {
/*
	    DLDdbg << "--DLD_run = " << DLD_run << endl << flush;
	    DLD_run--;
*/
	 }
	 else {
	    if (i->second)
	       i->second->parse();
	 }	
      }
      else if(errno == ECHILD)
      {
	 map<int, DLD_Gauge_Ptr>::iterator i;
	 for(i = gaugemap.begin(); i != gaugemap.end(); ++i) {
	    if (i->second)
		  i->second->parse();
	 }
      }
   } while (pid > 0);

   if((DLD_run >= 0) && !DLD_error)
      return true;
   else 
      return false;
}

 void DLD_Gui::
register_gauge(DLD_Gauge *_gauge, int _fd) 
{
   gaugemap[_fd] = _gauge;
}

 void DLD_Gui::
deregister_gauge(DLD_Gauge *_gauge) 
{
   for(map<int, DLD_Gauge_Ptr>::iterator i = gaugemap.begin();
       i != gaugemap.end(); ++i) {
      if (i->second == _gauge) {
	 gaugemap.erase(i);
	 close(i->first);
	 break;
      }
   }
}

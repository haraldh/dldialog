/******************************************************************************
**
** $Id: dld_lib.cc,v 1.1 2001/03/14 02:33:18 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "../dld_lib.h"
#include "dld_tvapp.h"
#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>

extern "C" DLD_Gui *
dld_lib_init (const char *name, int argc, char **argv)
{
   dup2 (tty_fdin, STDIN_FILENO);
   dup2 (tty_fdout, STDOUT_FILENO);
   dup2 (tty_fderr, STDERR_FILENO);

   /* 
    * We don't want to go in the background.
   */
   signal(SIGTTIN, SIG_IGN);
   signal(SIGTTOU, SIG_IGN);

   int oldsid = tcgetpgrp (tty_fdin);

   /*
    * Steal the Terminal. 
    * Good for the SIGWINSZ.
    */
   if(tcsetpgrp (tty_fdin, getpid()) != 0) {
      DLDerr << strerror(errno);
   }

   /*
    * Lets be the master of the session.
    * Good for the console.
    */
   setsid();   

   return new DLD_TVApp (name, oldsid, argc, argv);
}

/******************************************************************************
**
** $Id: dldialog.h,v 1.1 2001/03/14 02:33:07 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/

#ifndef DLD_DLDIALOG_H
#define DLD_DLDIALOG_H

#include <fstream>
#include <string>
#include <sys/un.h>        /* struct sockaddr_un */
#include <sys/socket.h>
#define DLD_SOCKET_DIR "/tmp/.dldialog"

/** Interface selection mode.
 * If you add a new interface you have to specify your
 * new mode here and set DLD_Mode accordingly.
 */
enum T_DLD_MODE {
   DLD_NONE,
   DLD_PARSE,
   DLD_GENERIC,
   DLD_TV,
   DLD_QT,
   DLD_RELOADED
};

///
extern T_DLD_MODE DLD_Mode;

///
extern int fd_out, fd_in, fd_err, sock_in;
extern struct  sockaddr_un  sock_addr;
extern socklen_t sock_len;

extern string inpath, indir;
char *dld_mytty ();
void print_usage ( const char *name );
void dld_make_fifo(int pid);

class DLD_Gui;
extern DLD_Gui *DLD_GUI;
extern DLD_Gui * (*func_dld_lib_init) (const char *name,
				       int argc, char **argv);
extern char dld_title[1024];
/// The global output stream.
extern fstream DLDout;

#endif

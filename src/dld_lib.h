/******************************************************************************
**
** $Id: dld_lib.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_LIB_H
#define DLD_LIB_H

#include <sys/types.h>
#include <fstream.h>		// for ifstream
#include <unistd.h>
#include <string>

class DLD_Gui;

/* IMPORTANT:
 *
 * If you change this, you also have to change
 * func_dld_lib_init in dldialog.cc
 */
extern "C" {
extern DLD_Gui *dld_lib_init (const char *name, int argc, char **argv);
}

#ifdef HAVE_CONFIG_H
#include <config.h>
#define DLD_VERSION_STRING VERSION
#else
#error NO CONFIG.H generated
#endif
#ifdef HAVE_GETTEXT
#include <libintl.h>
#else
#include "intl/libintl.h"
#endif

#define _(String) gettext (String)

extern string convstr (const string& str);

/// The global error stream.
extern ofstream DLDerr;
/// The global debugging stream.
extern ofstream DLDdbg;
/// The corresponding tty values
extern int tty_fdout, tty_fdin, tty_fderr;

#ifdef DEBUG
#include <exception>

/** An assertion function for use with dldialog
 */
template <class X, class A> inline void DLD_Assert(A assertion, 
						   const char *_assert,
						   const char *file, int line)
{
   if(!assertion) throw X(_assert, file, line);
}

/// A generic exception
class DLD_Exception : public exception {
public:
   DLD_Exception(const char *_reason,
		 const char *_file, int _line): 
      reason(_reason),
      file(_file),
      line(_line) {};

   string reason;
   string file;
   int line;
};

/// Bad argument exception
class Bad_arg : public DLD_Exception {
public:  
   Bad_arg(const char *_assert, const char *_file, int _line): 
      DLD_Exception(_assert, _file, _line) {};
};

#define Assert(X, A) DLD_Assert<X>(A, #X " " #A, __FILE__, __LINE__);
#else
#define Assert(X, A) 
#endif
#endif

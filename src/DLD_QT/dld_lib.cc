/******************************************************************************
**
** $Id: dld_lib.cc,v 1.1 2001/03/14 02:33:12 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_qtapp.h"

extern "C" DLD_Gui *
dld_lib_init (const char *name, int argc, char **argv)
{
   return new DLD_QTApp (name, argc, argv);
}

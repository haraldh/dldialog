/******************************************************************************
**
** $Id: dld_tvcheck.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_tvlib.h"
#include "dld_tvcheck.h"
#include <iostream.h>

DLD_TVCheckButton::
DLD_TVCheckButton (const string& name, DLD_TVDialog *pd):
   DLD_TVObj (name, pd)
{
}

DLD_TVCheckButton::
~DLD_TVCheckButton ()
{
}

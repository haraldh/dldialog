/******************************************************************************
**
** $Id: dld_tvradio.cc,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_tvlib.h"
#include "dld_tvradio.h"
#include <iostream.h>

DLD_TVRadioButton::
DLD_TVRadioButton (const string& name, DLD_TVDialog *pd):
   DLD_TVObj (name, pd)
{
}

DLD_TVRadioButton::
~DLD_TVRadioButton ()
{
}


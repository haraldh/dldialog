/******************************************************************************
**
** $Id: dld_comboitem.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_comboitem.h"

#include <iostream.h>

DLD_QTComboItem:: 
DLD_QTComboItem (const string& name, DLD_QTDialog *pd):
   DLD_QTObj (name, pd)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "comboitem " << dld_name << " created\n";
#endif
}

DLD_QTComboItem::
~DLD_QTComboItem ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "comboitem " << dld_name << " deleted\n";
#endif
}

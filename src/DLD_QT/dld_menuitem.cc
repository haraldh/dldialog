/******************************************************************************
**
** $Id: dld_menuitem.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** by Harald Hoyer (HarryH@Royal.Net) for delix Computer GmbH (http://www.delix.de)
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_menuitem.h"

#include <iostream.h>

DLD_Menuitem: : DLD_Menuitem (const char *name, DLD_QTObj * par):QPushMenuitem (name, par->qwidget), DLD_QTObj (name, this)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "menuitem ";
#endif
   setMinimumSize (sizeHint ());
   par->insert ((QWidget *) this, this);
   connect (this, SIGNAL (clicked ()), SLOT (slot_activate ()));
}

DLD_Menuitem: :~DLD_Menuitem ()
{
}

int DLD_Menuitem::
create ()
{
   DLD_Obj::create();
   return 0;
}

int DLD_Menuitem::
slot_activate ()
{
   if (doexit)
   {
    DLD_QTObj: :activate ();
      get_parent ()->done (0);
   }

   return 0;
}

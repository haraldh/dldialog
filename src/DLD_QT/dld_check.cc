/******************************************************************************
**
** $Id: dld_check.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
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
#include "dld_check.h"
#include "dld_dialog.h"
#include <iostream.h>

DLD_QTCheckButton:: 
DLD_QTCheckButton (QWidget *_parent, const string& name, DLD_QTDialog *pd):
   QCheckBox (convstr(name).c_str(), _parent),
   DLD_QTObj (name, pd)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "check ";
#endif
   setMinimumSize (sizeHint ());
   connect (this, SIGNAL (toggled ( bool )), SLOT (slot_activate ( bool )));
}

DLD_QTCheckButton::
~DLD_QTCheckButton ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "check deleted\n";
#endif
}

void DLD_QTCheckButton::
create ()
{
   if (test_env ())
      setChecked (TRUE);
   DLD_Obj::create();
}

void DLD_QTCheckButton::
slot_activate(bool on)
{
   if(on) {
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "checkbutton " 
	  << " toggled on" << endl << flush;
#endif      
      DLD_QTObj::activate();
      emit signal_cbpress();
   }
   else {
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "checkbutton " 
	  << " toggled off" << endl << flush;
#endif      
      DLD_QTObj::deactivate();
      emit signal_cbpress();
   }
}

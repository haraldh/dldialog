/******************************************************************************
**
** $Id: dld_radio.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_radio.h"
#include "dld_dialog.h"
#include <iostream.h>

DLD_QTRadioButton::
DLD_QTRadioButton (int num, QWidget *_parent, 
			    const string& name, DLD_QTDialog *pd):
   QRadioButton (convstr(name).c_str(), _parent),
   DLD_QTObj (name, pd),
   mynum(num)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "radio ";
#endif
   setMinimumSize (sizeHint ());
   connect (this, SIGNAL (toggled ( bool )), SLOT (slot_activate ( bool )));
}

DLD_QTRadioButton::
~DLD_QTRadioButton ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "radio deleted\n";
#endif
}

void DLD_QTRadioButton::
create ()
{
   DLD_Obj::create();
}

void DLD_QTRadioButton::
slot_activate(bool on)
{
   if(on) {
#ifdef DEBUG
      DLDdbg << DLD_LIB_PREFIX "radiobutton " << mynum 
	     << " toggled on" << endl << flush;
#endif      
      emit signal_rbpress(mynum);
      DLD_QTObj::activate();
   }
   else {
#ifdef DEBUG
      DLDdbg << DLD_LIB_PREFIX "radiobutton " << mynum 
	     << " toggled off" << endl << flush;
#endif
      DLD_QTObj::deactivate();
   }
}

/******************************************************************************
**
** $Id: dld_checklist.cc,v 1.1 2001/03/14 02:33:07 saturn_de Exp $
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
#include "dld_checklist.h"
#include "dld_check.h"
#include "dld_qtapp.h"
#include <iostream.h>
#include <qbutton.h>

DLD_QTCheckList::
DLD_QTCheckList (QWidget *_parent, 
			    const string& name, DLD_QTDialog *pd):
   QButtonGroup (convstr(name).c_str(), _parent),
   DLD_QTObj (name, pd),
   count (0)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "checklist ";
#endif
   topLayout = new QVBoxLayout ((QGroupBox *) this, QT_BORDER * 2, QT_BORDER);
   if (dld_name.length() == 0)
      QButtonGroup::setFrameStyle (NoFrame);
}

DLD_QTCheckList::
~DLD_QTCheckList ()
{
//   update_var();
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "checklist delete";
#endif
}

DLD_CheckButton * DLD_QTCheckList::
checkbutton (const string& name)
{
   DLD_QTCheckButton *p = new DLD_QTCheckButton(this, name, pardia);
   topLayout->addWidget (p);
   insert(p, count);

   connect (p, SIGNAL (signal_cbpress()), 
	    this, SLOT (slot_cbpress()));

   add_child(p);
   count++;
   return p;
}

void DLD_QTCheckList::
create (void)
{
   topLayout->activate ();

   int i;
   QString istr;

   for (i = 0; i < count; i++)
   {
      if (test_env(string(istr.setNum (i + 1))))
      {
	 QButton *obj = find (i);
	 if (obj)
	 {
	    if(!obj->isOn ()) {
	       obj->animateClick ();
	    }
#ifdef DEBUG
	    DLDdbg << DLD_LIB_PREFIX "checklist activate " << i << "\n";
#endif
	 }
      }
   }

//   pardia->dld_app->processEvents();

   for(CI i = childlist.begin(); i != childlist.end(); ++i) {
      (*i)->create ();
   }
   DLD_Obj::create();
}

void  DLD_QTCheckList::
update_var()
{
   QString str (""), istr;
   int i;

   for (i = 0; i < count; i++)
   {
      QButton *obj = find (i);
      if (obj)
      {
	 if (obj->isOn ())
	 {
	    str += istr.setNum (i + 1) + QString (" ");
#ifdef DEBUG
	    DLDdbg << DLD_LIB_PREFIX "checklist " << i << " is active\n";
#endif
	 }
      }
   }

   varvalue = str;
 
   activate ();
}

void DLD_QTCheckList::
slot_cbpress ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "checkbutton " 
	  << " pressed" << endl << flush;
#endif      
   update_var();
}

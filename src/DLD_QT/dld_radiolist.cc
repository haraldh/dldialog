/******************************************************************************
**
** $Id: dld_radiolist.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
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
#include "dld_radiolist.h"
#include "dld_qtapp.h"
#include <iostream.h>
#include <qbutton.h>

DLD_QTRadioList:: 
DLD_QTRadioList (QWidget *_parent, 
			    const string& name, DLD_QTDialog *pd):
   QButtonGroup (convstr(name).c_str(), _parent),
   DLD_QTObj (name, pd),
   count (0)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "radiolist constructed" << endl << flush;
#endif   

   if (dld_name.length() == 0)
      QButtonGroup::setFrameStyle (NoFrame);

   topLayout = new QVBoxLayout ((QGroupBox *) this, QT_BORDER * 2, QT_BORDER);
}

DLD_QTRadioList::
~DLD_QTRadioList ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "radiolist delete" << endl << flush;
#endif
}

DLD_RadioButton * DLD_QTRadioList::
radiobutton(const string& name)
{
   DLD_QTRadioButton *rb = new DLD_QTRadioButton(count, this, name, pardia);

   topLayout->addWidget (rb);

   add_child(rb);
   rb_childlist.push_back(rb);

   insert(rb, count);

   connect (rb, SIGNAL(signal_rbpress(int)), 
	    this, SLOT(slot_rbpress(int)));

   count++;

   return rb;
}

void DLD_QTRadioList::
create (void)
{
   topLayout->activate ();
   bool wasset=false;
   int i;
   QString istr;

   // First activate all radiobuttons
   for(RBI i = rb_childlist.begin(); i != rb_childlist.end(); ++i) {
      if((*i)->test_env()) {
         (*i)->animateClick();
         wasset=true;
      }
   }

   // Now check my own variable.
   for (i = 0; i < count; i++)
   {
      if (test_env (string(istr.setNum (i + 1))))
      {
	 QButton *obj = find (i);
	 if (obj)
	 {
	    obj->animateClick ();
            wasset=true;
#ifdef DEBUG
	    DLDdbg << DLD_LIB_PREFIX "radiolist activate " << i << "\n";
#endif
	 }
      }
   }   

   if(!wasset) {
      QButton *obj = find (0);
      if (obj)
      {
         obj->animateClick ();
      }
   }

//   pardia->dld_app->processEvents();

   for(RBI i = rb_childlist.begin(); i != rb_childlist.end(); ++i) {
      (*i)->create ();
   }
   DLD_Obj::create();
}

void DLD_QTRadioList::
slot_rbpress (int num)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "radiobutton " << num 
	  << " pressed" << endl << flush;
#endif      
   varvalue = QString().setNum (num + 1);
   DLD_QTObj::activate ();
}

/******************************************************************************
**
** $Id: dld_combobox.cc,v 1.1 2001/03/14 02:33:08 saturn_de Exp $
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
#include "dld_combobox.h"
#include "dld_comboitem.h"
#include "dld_qtapp.h"
#include <qstring.h>
#include <iostream.h>
DLD_QTComboBox:: 
DLD_QTComboBox (QWidget *_parent, 
		const string& name, DLD_QTDialog *pd):
   QComboBox (FALSE, _parent, convstr(name).c_str()),
   DLD_QTObj (name, pd)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "combobox " << dld_name << " constructed\n";
#endif
}

DLD_QTComboBox::
~DLD_QTComboBox ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "combobox " << dld_name << " deleted\n";
#endif
}

void DLD_QTComboBox::slot_activated(int index)
{
   QString str ("");
   int cnt = count ();

   for (int i = 0; i < cnt; i++)
   {
      if(i != index) {
	 DLD_QTObj *obj = citems[i];
	 if (obj)
	 {
#ifdef DEBUG
	    DLDdbg << DLD_LIB_PREFIX "comboitem deactivate " 
		   << i << "\n";
#endif
	    obj->deactivate();
	 }
      }
   }

   DLD_QTObj *obj = citems[index];
   if (obj)
   {
      str.setNum (index + 1);
#ifdef DEBUG
	    DLDdbg << DLD_LIB_PREFIX "comboitem activate " 
		   << index << "\n";
#endif
      obj->activate ();
   }

   varvalue = str;

   activate ();
}

DLD_ComboItem *DLD_QTComboBox::comboitem(const string& name)
{
   DLD_QTComboItem *lbi = new DLD_QTComboItem(name, pardia);
   QComboBox::insertItem (lbi->dld_name.c_str());
   citems[count()-1] = lbi;
   return lbi;
}

void DLD_QTComboBox::
create (void)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "combobox create\n";
#endif
   QString str, istr;
   int i, cnt = count ();

   setFixedHeight (sizeHint ().height());
   fixed_height = true;
   setMinimumWidth (sizeHint ().width());

   if(cnt) {

      connect(this, SIGNAL(activated(int)),
              this, SLOT(slot_activated(int)));
      
      bool wasset=false;
      
      for (i = 0; i < cnt; i++)
      {
         DLD_QTObj *obj = citems[i];
         if (obj)
         {
            if (obj->test_env ())
            {
               setCurrentItem(i);
               slot_activated(i);
               wasset=true;
#ifdef DEBUG
               DLDdbg << DLD_LIB_PREFIX "comboitem activate " << i << "\n";
#endif
            }
         }
#ifdef DEBUG
         else DLDdbg << DLD_LIB_PREFIX "combobox error at " << i << "\n";
#endif
         
      }
      
      for (i = 0; i < cnt; i++)
      {
         if (test_env (string(istr.setNum (i + 1))))
         {
            setCurrentItem(i);
            slot_activated(i);
            wasset=true;
#ifdef DEBUG
            DLDdbg << DLD_LIB_PREFIX "combobox activate " << i << "\n";
#endif
         }
#ifdef DEBUG
         else DLDdbg << DLD_LIB_PREFIX "combobox " << istr << " not active\n";
#endif
      }
      
      if (!wasset) {
         setCurrentItem(0);
         slot_activated(0);
      }
      
//   pardia->dld_app->processEvents();
      
      for (i = 0; i < cnt; i++)
      {
         DLD_QTObj *obj = citems[i];
         if (obj)
         {
            obj->create();
         }
      }
      DLD_Obj::create();
   }
}




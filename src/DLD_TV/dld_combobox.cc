/******************************************************************************
**
** $Id: dld_combobox.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_combobox.h"
#include "dld_comboitem.h"
#include "dld_dialog.h"
#include <stdio.h>

DLD_TVComboBox::
DLD_TVComboBox(const string& _name, DLD_TVDialog *_parent) :
   DLD_TVObj(_name, _parent),
   TStaticInputLine(TRect(0,0,128,1), 128,  &ilist),
   ilist(0,1),
   item_nr(0)
{
   lenWidth.setMin(2);
   lenHeight.setMin(1);
   lenHeight.setPref(1);
   ibox = new DLD_NTVComboBox(TRect(0,0,1,1), this, &ilist);
}

DLD_TVComboBox::
~DLD_TVComboBox()
{
//  ibox is deleted by the window
//   delete ibox;
}

void DLD_TVComboBox::
create()
{   
   bool activated=false;
   int no=0;

   if(item_nr) {

      // First check the items
      for(IMI i = itemmap.begin(); i != itemmap.end(); ++i,++no) {
         if(i->second && i->second->test_env()) {
            ccIndex index = list->indexOf((char *)i->second->dld_name.c_str());
            TStaticInputLine::newData((char *)TStaticInputLine::list->at(index));
            i->second->activate();
            activated=true;
         }
      }

      // Then check our own variable
      for(IMI i = itemmap.begin(); i != itemmap.end(); ++i,++no) {
         char itemno[100];
         sprintf(itemno, "%d", i->second->getNumber()+1);

         if(i->second && test_env(itemno)) {
            ccIndex index = list->indexOf((char *)i->second->dld_name.c_str());
            TStaticInputLine::newData((char *)TStaticInputLine::list->at(index));
            i->second->activate();
            activated=true;
         }
      }

      if (!activated) {
         IMI i = itemmap.begin();
         ccIndex index = list->indexOf((char *)i->second->dld_name.c_str());
         TStaticInputLine::newData((char *)TStaticInputLine::list->at(index));
         i->second->activate();
         char buf[100];
         sprintf(buf, "%d", i->second->getNumber()+1);
         varvalue = buf;
         deactivate();
         activate();
      }
      dia->insert(ibox);
   } else {
      ibox->disable();
   }

   DLD_Obj::create();
   for(IMI i = itemmap.begin(); i != itemmap.end(); ++i,++no) {
      if(i->second) {
	 i->second->create();
      }
   }
   DLD_Obj::create();
}
   
void DLD_TVComboBox::
changeBounds( const TRect& bounds )
{   
#ifdef DEBUG
   DLDdbg << "ComboBox change bounds" << endl << flush;
#endif
   TStaticInputLine::changeBounds(bounds);
}
   
void DLD_TVComboBox::
calcBounds(TRect& bounds, TPoint)
{
#ifdef DEBUG
   DLDdbg << "ComboBox calc bounds" << endl << flush;
#endif
   bounds = geom;   
}

DLD_ComboItem *DLD_TVComboBox::
comboitem(const string& name)
{
   DLD_TVComboItem *p = new DLD_TVComboItem(name, dia, item_nr);

   add_child(p);

   itemmap[name] = p;
   ilist.insert(newStr(p->dld_name.c_str()));

   item_nr++;

   lenWidth.setMin(max(p->dld_name.length()+3, lenWidth.getMin()));

   return p;
}

void DLD_TVComboBox::
setGeom( const TRect& geom ) 
{
#ifdef DEBUG
   DLDdbg << "ComboBox set geom" << endl << flush;
#endif

   TRect nb(geom);
   nb.b.x--;
   DLD_TVObj::setGeom(nb);
   ibox->setGeom(geom);
}

void DLD_TVComboBox::
newData(char *val)
{
   if(! (val && strlen(val)))
      return;

   TStaticInputLine::newData(val);

   const string str(val);
   DLD_TVComboItem *item = itemmap[str];

   for(IMI i = itemmap.begin(); i != itemmap.end(); ++i) {      
      if ( i->second != item) 
      	 i->second->deactivate();
   }

   if ( item ) {
      item->activate();
      char buf[100];
      sprintf(buf, "%d", item->getNumber()+1);
      varvalue = buf;
      deactivate();
      activate();
   }
}


void DLD_TVComboBox::handleEvent( TEvent& event ) 
{
   if(item_nr)
      TStaticInputLine::handleEvent(event);
}

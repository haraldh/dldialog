/******************************************************************************
**
** $Id: dld_list.cc,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**      This program is free software; you can redistribute it and/or
**      modify it under the terms of the GNU General Public License
**      as published by the Free Software Foundation; either version
**      2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#define Uses_TListBox
#define Uses_TScrollBar
#define Uses_TEvent
#define Uses_TKeys

#include "dld_tvlib.h"
#include "dld_list.h"
#include "dld_listitem.h"
#include "dld_dialog.h"
#include <stdio.h>
#include <iostream.h>

DLD_ScrollBar::DLD_ScrollBar(const TRect a, DLD_TVDialog *pd)
   : TScrollBar(a) 
{
   pd->insert(this);
//   options |= ofFramed;
};


DLD_TVList:: 
DLD_TVList (const string& name, DLD_TVDialog * pd):
   DLD_TVObj (name, pd),
   TListBox(TRect(0,0,1,1), 1, 
            aScrollBar= new DLD_ScrollBar(TRect(0,0,1,3), pd)),
   listcol(0,1),
   list_ctr(0),
   was_double(false)
{
   is_multi = false;
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "list " << flush ;
#endif
   
   options |= ofFramed;

   height = 2;
   width = dld_name.length() - (hotk) * 2 + 6;

   lenHeight.setMin(height);
   lenWidth.setMin(width);

   if(dld_name.length()) {
      label = new TLabel(TRect(2, 1, width, 2),
                         dld_name.c_str(), this);
      dia->insert(label);
   }
   else label = 0;

//   tag='*';
   tag='\020';
}

DLD_TVList::
~DLD_TVList ()
{
#ifdef DEBUG
   DLDdbg << "~list " << dld_name << "\n";
#endif
}

void DLD_TVList::
create()
{
   DLD_Obj::create();
}
   
void DLD_TVList::
changeBounds( const TRect& bounds )
{
   if(label)
      label->moveTo(bounds.a.x+3, bounds.a.y);


   TRect nb(bounds), sb(bounds);
   nb.grow(-2,-1);

   if(aScrollBar) {
      sb.grow(-1,-1);
      sb.b.x = sb.a.x+1;
      aScrollBar->setGeom(sb);
   }
   TListBox::changeBounds(nb);
}
   
void DLD_TVList::
calcBounds(TRect& bounds, TPoint)
{
   bounds = geom;
}
   
DLD_ListItem * DLD_TVList::
listitem (const string& _name)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "list insert " << _name << endl << flush ;
#endif

   DLD_TVListItem *p = new DLD_TVListItem(_name, dia);

   add_child(p);

   childarray.push_back(p);

   // We use atInsert otherwise we get a sorted list
   listcol.atInsert(list_ctr, newStr((string(" ") + conname(_name)).c_str()));

   list_ctr++;

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "list inserted " << _name << endl << flush ;
#endif

   width = max(_name.length()+5, width);
   height++;

   return p;
}

void DLD_TVList::
open_brace()
{
}
   
void DLD_TVList::
close_brace()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "list close_brace" << endl << flush ;
#endif
   bool items[list_ctr];
   bool wasset=false;
   newList(&listcol);


   // First check the items
   for (unsigned int i=0; i < list_ctr; i++) {
      if(childarray[i] && childarray[i]->test_env()) {
         items[i] = true;
         wasset=true;
      }
      else
         items[i] = false;
   }

   for (unsigned int i=0; i < list_ctr; i++) {
      if(items[i]) {
         focusItem(i);
         ToggleItem(i);
      }
   }

   // Then check our own variable
   for (unsigned int i=0; i < list_ctr; i++) {
      char itemno[10];
      sprintf(itemno, "%d", i+1);
      if(test_env(itemno)) {
         items[i] = true;
         wasset=true;
      }
      else 
         items[i] = false;
   }

   for (unsigned int i=0; i < list_ctr; i++) {
      if(items[i]) {
         focusItem(i);
         ToggleItem(i);
      }
   }

   if(!wasset || is_multi) {
      focusItem(0);
      if(!is_multi)
        ToggleItem(0);
   }

   // For the scrollbar
   width+=2;

   lenHeight.setMin((height > 7) ? 7 : height);
   lenWidth.setMin((width > 10) ? 10 : width);
   lenWidth.setPref(width);
   lenHeight.setPref(height);

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "list h=" << height << " w=" << width << "\n";
#endif

   for (unsigned int i=0; i < list_ctr; i++) {
      if(childarray[i]) {
         childarray[i]->create();
      }
   }
   create();
   update_var();
}

void DLD_TVList::selectItem( short item )
{
   TListBox::selectItem( item );

   if(!is_multi) {       
      for (unsigned int i=0; i < list_ctr; i++) {
         char *itemaddr;
         itemaddr=(char *)(list()->at(i));
         itemaddr[0]=' ';
      }


      for(CI i = childarray.begin(); i != childarray.end(); ++i) {
         (*i)->deactivate();
      }
   }   
   ToggleItem(item);
}

void DLD_TVList::handleEvent(TEvent& event)
{
   if(is_multi) {
      // we dont want to lose mouse button events to the main handler....
      if ((event.what==evMouseDown) && (event.mouse.buttons==mbLeftButton))
      {
         was_double=false;
         // Small workaround to exit only if the item was double clicked
         if (event.mouse.eventFlags & meDoubleClick) {
            was_double = true;
         }
         TListBox::handleEvent(event);
         ToggleItem(focused);
         TListBox::draw();
      }
      else
         TListBox::handleEvent(event);
      
      switch (event.what)
      {
      case evKeyDown:
         switch(event.keyDown.keyCode)
         {
         case kbEnter:
            if ( focused < range ) {
               ToggleItem(focused);
            }
            break;
         case kbF7:
            MarkAll();
            break;
         case kbF8:
            UnMarkAll();
            break;
         case kbF9:
            ToggleAll();
            break;
         default:
            int n=0;
            for(CI i = childarray.begin(); i != childarray.end();
                ++i, ++n) {
               string name = (*i)->dld_name;
               if(event.keyDown.charScan.charCode == name[0]) {
                  clearEvent(event);
                  focusItem(n);
                  break;
               }
            }
            break;
         }
         TListBox::draw();
         break;
      }
   }
   else {
      // we dont want to lose mouse button events to the main handler....
      if ((event.what==evMouseDown) && (event.mouse.buttons==mbLeftButton))
      {
         was_double=false;
         // Small workaround to exit only if the item was double clicked
         if (event.mouse.eventFlags & meDoubleClick) {
            was_double = true;
         }

         TListBox::handleEvent(event);
         selectItem(focused);
         TListBox::draw();

      }
      else
      {
         TListBox::handleEvent(event);
         if (event.what == evKeyDown) {
            switch(event.keyDown.keyCode) {
            case kbEnter:
               if ( focused < range ) {
                  was_double = true;
                  focusItemNum(focused);
                  selectItem(focused);
               }
               clearEvent(event);
               break;
            }
         }
      }
   }
}

void DLD_TVList::ToggleItem(int item_no)
{
   if (range<=0)
      return;
   
   char *itemaddr;
   itemaddr=(char *)(list()->at(item_no));
   if (itemaddr[0]==tag) {
      if(childarray[item_no])
         childarray[item_no]->deactivate ();
      itemaddr[0]=' ';
   }
   else {
      if(childarray[item_no]) {
         if (!was_double && childarray[item_no]->is_exit()) {
            childarray[item_no]->set_exit(false);
            childarray[item_no]->activate ();
            childarray[item_no]->set_exit(true);
         }
         else {
            childarray[item_no]->activate ();
            was_double = false;
         }
      }
      itemaddr[0]=tag;
   }
   update_var();
}

void DLD_TVList::MarkAll()
{
   if (range<=0)
      return;

   char *itemaddr;
   for (int i=0;i<range;i++)
   {
      itemaddr=(char *)(list()->at(i));
      itemaddr[0]=tag;
      if(childarray[i])
         childarray[i]->activate ();
   }
   update_var();
}

void DLD_TVList::UnMarkAll()
{
   if (range<=0)
      return;
   char *itemaddr;
   for (int i=0;i<range;i++)
   {
      itemaddr=(char *)(list()->at(i));
      if(childarray[i])
         childarray[i]->deactivate ();
      itemaddr[0]=' ';
   }
   varvalue.erase();
}

void DLD_TVList::ToggleAll()
{
   if (range<=0)
      return;
   char *itemaddr;
   for (int i=0;i<range;i++)
   {
      itemaddr=(char *)(list()->at(i));
      if (itemaddr[0]==tag) {
         if(childarray[i])
            childarray[i]->deactivate ();
         itemaddr[0]=' ';
      }
      else {
         if(childarray[i])
            childarray[i]->activate ();
         itemaddr[0]=tag;
      }
   }
   update_var();
}

void DLD_TVList::
update_var()
{
   if(!is_created)
      return;
   
   char istr[512];

   varvalue.erase();
   
   for (unsigned int i = 0; i < list_ctr; i++)
   {
      unsigned char *itemaddr;
      itemaddr=(unsigned char *)(list()->at(i));
      if (itemaddr[0]==tag) {
         if (childarray.size()>=i)
         {
            if(is_multi)
               sprintf(istr, "%d ", i+1);
            else
               sprintf(istr, "%d", i+1);
            varvalue += istr;
         }
      }
   }

   activate();
}

/******************************************************************************
**
** $Id: dld_checklist.cc,v 1.1 2001/03/14 02:33:14 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

/** TODO
 *
 * - add childs to a list and destroy them
 *
 */

#define Uses_TGroup
#define Uses_TRect
#define Uses_TBackground
#define Uses_TStringCollection 

#include "dld_checklist.h"
#include "dld_tvlib.h"
#include "dld_tvcheck.h"
#include "dld_text.h"
#include "dld_dialog.h"
#include <iostream.h>
#include <stdio.h>
#include <string.h>

DLD_TVCheckList::
DLD_TVCheckList (const string& name, DLD_TVDialog *pd):
   DLD_TVObj (name, pd),
   TCheckBoxes (TRect(2,2,0,0), NULL)
{
   // Cope with bad implementation in tvision
   delete strings;
   strings = new TStringCollection( 0, 1 );

   check_ctr = 0;
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "checklist \n" ;
#endif
   growMode = gfFixed;
   height = 2;
   width = dld_name.length() - (hotk) * 2 + 4;

   lenWidth.setMin(width);
   lenHeight.setMin(height);   

   for (int i = 0; i < 32; i++)
   {
      check[i] = 0;
   }

   
   if(dld_name.length()) {
      options |= ofFramed;
      label = new TLabel(TRect(2, 1, width, 2),
			 dld_name.c_str(), this);
      dia->insert(label);
   }
   else label = 0;
}

DLD_TVCheckList::
~DLD_TVCheckList ()
{
   update_var();
#ifdef DEBUG
   DLDdbg << "~checklist " << dld_name << "\n";
   DLDdbg.flush ();
#endif
}

void DLD_TVCheckList::
close_brace ()
{
#ifdef DEBUG
   DLDdbg << "checklist " << dld_name 
	  << "(" << width << "," << height << ")\n";
   DLDdbg.flush ();
#endif
   lenWidth.setMin(width);
   lenHeight.setMin(height);   
   lenWidth.setPref(width);
   lenHeight.setPref(height);   

}

void DLD_TVCheckList::
create ()
{
   for (int i = 0; i < check_ctr; i++)
   {
      char num[4];
      sprintf(num, "%d", i+1);      
      if(test_env(string(num)) || check[i]->test_env())
	 TCheckBoxes::press(i);
   }
   draw();
   update_var();
   for (int i = 0; i < check_ctr; i++)
   {
      check[i]->create();
   }   
   DLD_Obj::create();
}

DLD_CheckButton *DLD_TVCheckList::
checkbutton(const string& name)
{
   string nstr = conname(name);

   DLD_TVCheckButton *p=0;

   if(check_ctr < 32) {
      check[check_ctr] = p = new DLD_TVCheckButton(name, dia);

      add_child(p);

      // We use atInsert otherwise we get a sorted list
      strings->atInsert( check_ctr, newStr(nstr.c_str()) );

      check_ctr++;
      height++;
      width = max(nstr.length() - (p->hotk) * 2 + 8, width);
   }
   else
      DLDerr << "No more than 32 Checkbuttons allowed due to TVision!\n";
   
   return p;
}

void DLD_TVCheckList::
changeBounds( const TRect& bounds)
{
   if(label)
      label->moveTo(bounds.a.x+1, bounds.a.y);

   TRect nb(bounds);
   nb.grow(-1,-1);
   TCheckBoxes::changeBounds(nb);
#ifdef DEBUG
   DLDdbg << "checklist changeBounds(" 
	  << bounds.a.x << "," << bounds.a.y << ")"
	  << "(" << bounds.b.x << "," << bounds.b.y << ")"
	  << endl;
#endif
}

void DLD_TVCheckList::
calcBounds(TRect& bounds, TPoint)
{
   bounds = geom;
}

void DLD_TVCheckList::
press(int item)
{
   TCheckBoxes::press(item);
   update_var();
}

void DLD_TVCheckList::
update_var()
{
   char istr[512];

   for (int i = 0; i < check_ctr; i++)
   {
      if (!(value & (1<<i)))
	 check[i]->deactivate ();
   }

   varvalue.erase();
   
   for (int i = 0; i < check_ctr; i++)
   {
      if (value & (1<<i)) {
	 if (check[i])
	 {
#ifdef DEBUG
	    DLDdbg << "~checklist " << dld_name << "activate " 
		   << check[i]->dld_name << "\n";
	    DLDdbg.flush ();
#endif
	    check[i]->activate ();
	    sprintf(istr, "%d ", i+1);
	    varvalue += istr;
	 }
      }
   }

   activate();
}

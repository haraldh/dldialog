/******************************************************************************
**
** $Id: dld_radiolist.cc,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#define Uses_TGroup
#define Uses_TRect
#define Uses_TBackground
#define Uses_TStringCollection 

#include "dld_radiolist.h"
#include "dld_tvlib.h"
#include "dld_tvradio.h"
#include "dld_text.h"
#include "dld_dialog.h"
#include <iostream.h>
#include <stdio.h>
#include <string.h>

DLD_TVRadioList::
DLD_TVRadioList (const string& name, DLD_TVDialog *pd):
   DLD_TVObj (name, pd),
   TRadioButtons (TRect(2,2,0,0), NULL)
{
   // Cope with bad implementation in tvision
   delete strings;
   strings = new TStringCollection( 0, 1 );

   radio_ctr = 0;
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "radiolist \n" ;
#endif
   growMode = gfFixed;
   height = 2;
   width = dld_name.length() - (hotk) * 2 + 4;

   lenWidth.setMin(width);
   lenHeight.setMin(height);   
   
   if(dld_name.length()) {
      label = new TLabel(TRect(2, 1, width, 2),
			 dld_name.c_str(), this);
      dia->insert(label);
      options |= ofFramed;
   }
   else label = 0;

   for (int i = 0; i < 32; i++)
   {
      radio[i] = 0;
   }


}

DLD_TVRadioList::
~DLD_TVRadioList ()
{
   update_var();
#ifdef DEBUG
   DLDdbg << "~radiolist " << dld_name << "\n";
   DLDdbg.flush ();
#endif

}

void DLD_TVRadioList::
close_brace ()
{
#ifdef DEBUG
   DLDdbg << "radiolist " << dld_name 
	  << "(" << width << "," << height << ")\n";
   DLDdbg.flush ();
#endif
   lenWidth.setMin(width);
   lenHeight.setMin(height);   
   lenWidth.setPref(width);
   lenHeight.setPref(height);   

   // First check the items
   for (unsigned int i = 0; i < radio_ctr; i++)
   {
      if(radio[i]->test_env()) {
	 press(i);
	 sel=i;
	 TRadioButtons::value = i;
#ifdef DEBUG
	 DLDdbg << "Radio " << i+1 << endl << flush;
#endif
      }
   }

   // Then check our own variable
   for (unsigned int i = 0; i < radio_ctr; i++)
   {
      char num[10];
      sprintf(num, "%d", i+1);      
      if(test_env(string(num))) {
	 press(i);
	 sel=i;
	 TRadioButtons::value = i;
#ifdef DEBUG
	 DLDdbg << "Radio " << i+1 << endl << flush;
#endif
      }
   }

}

void DLD_TVRadioList::
create ()
{
   draw();
   for ( unsigned int i = 0; i < radio_ctr; i++) {
      if (i != TRadioButtons::value )
	 radio[i]->create ();
   }
   DLD_Obj::create();
}

DLD_RadioButton *DLD_TVRadioList::
radiobutton(const string& name)
{
   Assert(Bad_arg, (radio_ctr < 32));
	  
   string nstr = conname(name);
   
   DLD_TVRadioButton *p  = new DLD_TVRadioButton(name, dia);

   add_child(p);

   radio[radio_ctr] = p ;

   // We use atInsert otherwise we get a sorted list
   strings->atInsert( radio_ctr, newStr(nstr.c_str()) );
   
   radio_ctr++;
   height++;
   width = max(nstr.length() - (p->hotk) * 2 + 8, width);
   
   return p;
}


void DLD_TVRadioList::
changeBounds( const TRect& bounds)
{
   if(label)
      label->moveTo(bounds.a.x+1, bounds.a.y);

   TRect nb(bounds);
   nb.grow(-1,-1);
   TRadioButtons::changeBounds(nb);

#ifdef DEBUG
   DLDdbg << "radiolist changeBounds(" 
	  << bounds.a.x << "," << bounds.a.y << ")"
	  << "(" << bounds.b.x << "," << bounds.b.y << ")"
	  << endl;
#endif
}

void DLD_TVRadioList::
calcBounds(TRect& bounds, TPoint)
{
   bounds = geom;
}

void DLD_TVRadioList::
press(int item)
{
#ifdef DEBUG
   DLDdbg << "Radio pressed " << item << endl << flush;
#endif
   TRadioButtons::press(item);
   update_var();
}

void DLD_TVRadioList::
movedTo(int item)
{
#ifdef DEBUG
   DLDdbg << "Radio moved to " << item << endl << flush;
#endif
   TRadioButtons::movedTo(item);
   update_var();
}

void DLD_TVRadioList::
update_var()
{
   char istr[512];

   for ( unsigned int i = 0; i < radio_ctr; i++) {
      if (i != TRadioButtons::value )
	 radio[i]->deactivate ();
   }

   if (radio[TRadioButtons::value])
   {
      radio[TRadioButtons::value]->activate ();
      sprintf(istr, "%ld", TRadioButtons::value+1);
      varvalue = istr;
      activate();
   }
}

/******************************************************************************
**
** $Id: dld_row.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#define Uses_TGroup
#define Uses_TRect
#define Uses_TBackground
#define Uses_TKeys
#define Uses_TFrame

#include "dld_row.h"
#include "dld_dialog.h"


DLD_TVRow::
DLD_TVRow(const string& _name, DLD_TVApp *aptr, DLD_TVDialog *dia) :    
   /*TView(TRect(0,0,1,1)),*/
   DLD_TVObj (_name, dia),
   DLD_TVContainer(_name, aptr, dia, DLD_TVContainer::O_HOR)
{
/*
   setState(sfVisible, False);
   options &=  ~ofSelectable;
*/
   if(dld_name.length()) {
//      options |= ofFramed;
//      setState(sfExposed, True);
      width = dld_name.length() - (hotk) * 2 + 6;

      lenWidth.setMin(width);
//      lenWidth.setSizeAdd(2);
      lenHeight.setSizeAdd(1);
      

      label = new TStaticText(TRect(2, 1, width, 2),
			 dld_name.c_str());
//			 dld_name.c_str(), dia);

      dia->insert(label);
//      label->putInFrontOf(this);
   }
   else label = 0;

}

DLD_TVRow::
~DLD_TVRow()
{
}

void DLD_TVRow::
create()
{
   DLD_TVContainer::create (); 
};

void DLD_TVRow::
changeBounds( const TRect& bounds) 
{
#ifdef DEBUG
   DLDdbg << "Row changeBounds(" << bounds.a.x << "," << bounds.a.y << ")"
	  << "(" << bounds.b.x << "," << bounds.b.y << ")"
	  << endl;
#endif


   TRect nb(bounds);

   if(label) {
      label->moveTo(bounds.a.x+1, bounds.a.y);
      nb.grow(-1,-1);
   }

   DLD_TVContainer::changeBounds(nb);

//   TView::changeBounds(nb);
}

void DLD_TVRow::
draw()
{
//   TView::draw();
/*
   TDrawBuffer b;
   b.moveChar(0, '*' , getColor(0x02), size.x);
   writeLine(0, 0, size.x, 1, b);
   writeLine(0, size.y-1, size.x, 1, b);

   b.moveChar(0, '*' , getColor(0x02), size.y);
   writeLine(0, 0, 1, size.y, b);
   writeLine(size.x-1, 0, 1, size.y, b);
*/
}

void DLD_TVRow::
insert(TView *p) 
{ 
   dia->insert(p); 
//   putInFrontOf(p);
}

void DLD_TVRow::
close_brace()
{
}

void DLD_TVRow::
setGeom(const TRect& _g) 
{ 
   geom = _g; 

   TRect nb(_g);

   if(label) {
      nb.grow(-1,-1);
      label->moveTo(geom.a.x+1, geom.a.y);
   }

   DLD_TVContainer::changeBounds(nb);
}

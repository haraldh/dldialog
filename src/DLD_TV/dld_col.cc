/******************************************************************************
**
** $Id: dld_col.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
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
#define Uses_TFrame
#define Uses_TRect
#define Uses_TBackground

#include "dld_col.h"
#include "dld_dialog.h"

/* TODO:
 *
 * - Add a frame around the col
 */


DLD_TVCol::DLD_TVCol(const string& _name, DLD_TVApp *_aptr, DLD_TVDialog *_dia) :
/*   TView(TRect(0,0,1,1)),*/
   DLD_TVObj (_name, _dia),
   DLD_TVContainer(_name, _aptr, _dia, DLD_TVContainer::O_VER)
{

//   options &=  ~ofSelectable;
//     setState(sfVisible, False);
   if(dld_name.length()) {
//      options |= ofFramed;
//      setState(sfShadow, True);
      width = dld_name.length() - (hotk) * 2 + 6;

      lenWidth.setMin(width);

//      lenWidth.setSizeAdd(2);
      
      lenHeight.setSizeAdd(1);

//      lenHeight.addChild(new Len(1,1,0));
      
      label = new TStaticText(TRect(2, 1, width, 2),
			      dld_name.c_str());
      /*TLabel*/

      dia->insert(label);
//      label->putInFrontOf(this);

   }
   else {
      label = 0;
   }

};

DLD_TVCol::~DLD_TVCol()
{
}

void DLD_TVCol::
create()
{
   DLD_TVContainer::create (); 
};

void DLD_TVCol::
changeBounds( const TRect& bounds) 
{
#ifdef DEBUG
   DLDdbg << "Col changeBounds(" << bounds.a.x << "," << bounds.a.y << ")"
	  << "(" << bounds.b.x << "," << bounds.b.y << ")"
	  << endl;
#endif


   TRect nb(bounds);

   if(label) {
      nb.grow(-1,-1);
      label->moveTo(bounds.a.x+1, bounds.a.y);
      label->draw();
   }

   DLD_TVContainer::changeBounds(nb);
//   TView::changeBounds(nb);

}

void DLD_TVCol::
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

void DLD_TVCol::
insert(TView *p) 
{ 
   dia->insert(p); 
//   putInFrontOf(p);
}

void DLD_TVCol::
close_brace()
{
//   if(dld_name.length()) 
//      lenHeight.addChild(new Len(1,1,0));
}

void DLD_TVCol::
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

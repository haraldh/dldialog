/******************************************************************************
**
** $Id: dld_form.cc,v 1.1 2001/03/14 02:33:18 saturn_de Exp $
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
#define Uses_TKeys
#define Uses_TFrame

#include "dld_form.h"
#include "dld_dialog.h"


DLD_TVForm::
DLD_TVForm(const string& _name, DLD_TVApp *_aptr, DLD_TVDialog *_dia) :    
   DLD_TVObj (_name, _dia),
   TView(TRect(0,0,1,1)),
   DLD_TVContainer(_name, _aptr, _dia, DLD_TVContainer::O_HOR)
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
      lenWidth.setSizeAdd(2);
      lenHeight.setSizeAdd(2);
      
      label = new TStaticText(TRect(2, 1, width, 2),
			      dld_name.c_str() /*, dia*/);

      dia->insert(label);
//      label->putInFrontOf(this);
   }
   else  label = 0;

}

DLD_TVForm::
~DLD_TVForm()
{
}

void DLD_TVForm::
create()
{
   DLD_TVContainer::create (); 
};

void DLD_TVForm::
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

   TView::changeBounds(nb);
}

void DLD_TVForm::
draw()
{
   TView::draw();
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

void DLD_TVForm::
insert(TView *p) 
{ 
   dia->insert(p); 
//   putInFrontOf(p);
}

void DLD_TVForm::
close_brace()
{
}

void DLD_TVForm::
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

/******************************************************************************
**
** $Id: dld_textbox.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#define Uses_TEvent
#define Uses_TKeys
#include "dld_textbox.h"
#include "dld_dialog.h"
DLD_TVTextBox::DLD_TVTextBox(const string& name, DLD_TVDialog *pd) :
   DLD_TVObj(name, pd),
   TFileViewer(TRect(0,0,2,2), 
	       hScrollBar= new DLD_ScrollBar(TRect(0,2,2,3), pd),
	       vScrollBar= new DLD_ScrollBar(TRect(2,0,3,2), pd)),
   doFile(false),
   label(0)
{
   lenWidth.setMin(5);
   lenHeight.setMin(5);
   options |= ofFramed;
   fileLines = new TLineCollection(5, 5);
}

DLD_TVTextBox::~DLD_TVTextBox()
{
}
  
void DLD_TVTextBox::create()
{
   if(doFile && dld_name.length()) {      
      label = new TLabel(TRect(0, 0, dld_name.length()+2 , 1),
			 dld_name.c_str(), this);
      dia->insert(label);
   }
   else {
      typedef string::size_type ST;
      ST b, e;
      b=0;
      string line;

      // Find newlines and feed them to the fileLines

      while((e = dld_name.find("\n", b)) != string::npos)
      {
	 line = dld_name.substr(b, e-b);
	 limit.x = max( limit.x, line.length() );
	 fileLines->insert( newStr( line.c_str() ) );
	 b = e+1;
      }

      line = dld_name.substr(b);
      limit.x = max( limit.x, line.length() );
      fileLines->insert( newStr( line.c_str() ) );
      isValid = True;
      limit.y = fileLines->getCount();
      
      label = 0;
   }

   setState(sfSelected, True);
   DLD_Obj::create();
}

void DLD_TVTextBox::set_filename(const string& fname)
{
   readFile(fname.c_str());
   doFile = true;
}

void DLD_TVTextBox::changeBounds( const TRect& bounds )
{
   if(label)
      label->moveTo(bounds.a.x+1, bounds.a.y-1);
   TFileViewer::changeBounds(bounds);
}

void DLD_TVTextBox::setGeom( const TRect& bounds )
{
   TRect nb(bounds), vsb(bounds), hsb(bounds);

   // Shrink, cause it's framed
   nb.grow(-1,-1);

   vsb.grow(0,-1);
   vsb.a.x = vsb.b.x-1;
   vScrollBar->setGeom(vsb);

   hsb.grow(-1,0);
   hsb.a.y = hsb.b.y-1;
   hScrollBar->setGeom(hsb);

   DLD_TVObj::setGeom(nb);
}
 
void DLD_TVTextBox::calcBounds(TRect& bounds, TPoint)
{
   bounds = geom;
}

void DLD_TVTextBox::handleEvent(TEvent& event)
{
   TFileViewer::handleEvent(event);
   switch (event.what)
   {
   case evKeyDown:
      switch(event.keyDown.keyCode)
      {
      case kbRight:
         scrollTo(delta.x + 1, delta.y);
         break;
      case kbLeft:
      {
         int x = (delta.x - 1);
         scrollTo( (x < 0) ? 0 : x , delta.y);
      }
         break;
      case kbDown:
         scrollTo(delta.x, delta.y + 1);
         break;
      case kbUp:
      {
         int y = (delta.y - 1);
         scrollTo( delta.x, (y < 0) ? 0 : y);
      }
         break;
      case kbPgDn:
      {
         TRect size(getBounds());
         scrollTo(delta.x, delta.y + (size.b - size.a).y);
      }
         break;
      case kbPgUp:
      {
         TRect size(getBounds());
         int y = (delta.y - (size.b - size.a).y);
         scrollTo( delta.x, (y < 0) ? 0 : y);
      }
         break;
      default:
         return;
      }
      clearEvent(event);                 
      break;
   default:
      return;
   }
}

/******************************************************************************
**
** $Id: dld_dialog.cc,v 1.1 2001/03/14 02:33:18 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#define Uses_TStatusLine
#define Uses_TMenuBar
#define Uses_TKeys

#include "dld_tvlib.h"
#include "dld_tvapp.h"
#include "dld_dialog.h"
#include <iostream.h>

DLD_TVDialog:: 
DLD_TVDialog (const string& _name, DLD_TVApp *_app, const DLD_Out _out):
   DLD_TVObj (_name, this),
//   TDialog (TRect(0,0,132,255), dld_name.c_str()),
   TDialog (_app->deskTop->getExtent(), dld_name.c_str()),
   TWindowInit (&TDialog::initFrame),
   DLD_TVContainer(_name, _app, this, DLD_TVContainer::O_VER),
   DLD_Dialog(_app, _out)
{
   ow = oh = 0;
   width = dld_name.length() + 10;
   height = 0;

   lenWidth.setMin(width);
   lenHeight.setMin(height);

   lenWidth.setPer(0);
   lenHeight.setPer(0);

   options |= ofTileable;
   flags = wfMove|wfGrow|wfClose|wfZoom;

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "dialog " << dld_name 
	  << "(" << width << "," << height << ")" 
	  << endl << flush;
#endif
   hide();
}

DLD_TVDialog::
~DLD_TVDialog ()
{
   // Remove us from the childlist
   app->del_child (this);
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "dialog " << dld_name << " deleted\n";
   DLDdbg.flush ();
#endif
   dia = 0;
}

void DLD_TVDialog::
close_brace()
{
   // Insert ourselves in the desktop
   app->deskTop->insert(this);
//   app->deskTop->insertBefore(app->deskTop->first(), this);
   create();
//   app->deskTop->redraw();
//   app->menuBar->draw();
//   app->statusLine->draw ();
   if(app->mainDialog == this)
      putInFrontOf(owner->last);
   selectNext(False);   
}

void DLD_TVDialog::
create ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "dialog " << dld_name << " create\n";
   DLDdbg.flush ();
#endif

   if(is_created)
      return;

   printvars=false;

   // First create our children
   DLD_TVContainer::create ();

   TRect newBounds;

   if(((signed)width > size.x || (signed)height > size.y) || 
      (lenWidth.getPer() || lenHeight.getPer())) 
   {
      // Height or Width specified
      if(lenWidth.getPer() == 0)
	 lenWidth.setPer(100);

      if(lenHeight.getPer() == 0)
	 lenHeight.setPer(100);

      newBounds = TRect(origin.x, origin.y, 
			origin.x + size.x * lenWidth.getPer() / 100 ,
			origin.y + size.y * lenHeight.getPer() / 100);
   }
   else {
      // Set the smallest size
      newBounds = TRect(origin.x, origin.y, 
			 origin.x + width+2,
			 origin.y + height+2);
   }

   // Fake to really update all gui elements the first time
   TRect fake(newBounds);
   fake.grow(-1,-1);
   TDialog::setBounds(fake);
   
   changeBounds(newBounds);
   show();

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "dialog " << dld_name << " width=" 
	  << width << " height=" << height << "\n";
   DLDdbg.flush ();
#endif
   DLD_Obj::create();
}

void DLD_TVDialog::
insert(TView *p)
{
   TDialog::insert(p);
}

void DLD_TVDialog::
changeBounds( const TRect& bounds)
{
   if(!is_created)
      return;

#ifdef DEBUG
   DLDdbg << "dldialog changeBounds(" << bounds.a.x << "," << bounds.a.y << ")"
	<< "(" << bounds.b.x << "," << bounds.b.y << ")"
	<< endl;
#endif 

   TRect nb(1, 1, bounds.b.x - bounds.a.x - 1, bounds.b.y - bounds.a.y - 1);

   if((nb.b.y != oh) || (nb.b.x != ow)) {
      
      DLD_TVContainer::changeBounds(nb);
      
      DLDdbg << "dldialog changeBounds(" << bounds.a.x << "," 
	     << bounds.a.y << ")"
	     << "(" << lenWidth.getLen()+2 << "," 
	     << lenHeight.getLen()+2 << ")"
	     << endl << flush;
      ow = nb.b.x;
      oh = nb.b.y;
   }

   TRect db(bounds.a.x, bounds.a.y, 
	    bounds.a.x + lenWidth.getLen()+2,
	    bounds.a.y + lenHeight.getLen()+2);
   
   TDialog::changeBounds(db);

}

void DLD_TVDialog::
calcBounds(TRect& bounds, TPoint delta )
{
   TDialog::calcBounds(bounds, delta );
}

void DLD_TVDialog::
handleEvent( TEvent& event )
{
   if (event.what == evCommand) {
      switch (event.message.command)
      {	 
      case cmOK:             //  Close current window
         event.message.command = cmClose;
         printvars = true;
         break;
      }
   }

   TDialog::handleEvent(event);

   if (event.what == evKeyDown) {
      switch (event.keyDown.keyCode) {
      case kbUp :
         focusNext(True);
         clearEvent(event);
         break;
      case kbDown :
         focusNext(False);
         clearEvent(event);
         break;
      }
   }
}

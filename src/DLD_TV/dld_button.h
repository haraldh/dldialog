/******************************************************************************
**
** $Id: dld_button.h,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_TVBUTTON_H
#define DLD_TVBUTTON_H

#include "../dld_button.h"
#include "dld_tvobj.h"
#define Uses_TRect
#define Uses_TButton
#define Uses_TDialog
#include <tvision/tv.h>

///
class DLD_TVButton : public DLD_TVObj, public DLD_Button,
		     public TButton
{
public:
   ///
   DLD_TVButton(const string& name, DLD_TVDialog *pd, 
		int _width, int _height);
   ///
   ~DLD_TVButton();
   
   ///
   virtual void activate();
   
   ///
   void create();
   
   ///
   void press();
   
   void changeBounds( const TRect& bounds );
   
   void calcBounds(TRect& bounds, TPoint delta );
   
   virtual TPalette& getPalette() const;
   virtual void disable() {
      DLD_Obj::disable();
      setState(sfDisabled, True);
      options &= ~ofSelectable;
   };

   virtual void handleEvent( TEvent& event );
   void drawState(Boolean down);
   const char * markers;
   const char * dld_title;
   /**
    * Draws the button.
    */
   virtual void draw();
};

#endif

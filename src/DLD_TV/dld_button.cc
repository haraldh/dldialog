/******************************************************************************
**
** $Id: dld_button.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#include "dld_tvlib.h"
#include "dld_button.h"

#define Uses_TRect
#define Uses_TEvent
#define Uses_TButton
#define Uses_TDialog
#include <tvision/tv.h>

#include "dld_dialog.h"

#include <iostream.h>

#define cpTVBDis "\x10\x0B\x0C\x0D\x0E\x0E\x0E\x0F"

const int cmGrabDefault = 61, cmReleaseDefault = 62;

DLD_TVButton::
DLD_TVButton (const string& _name, DLD_TVDialog *pd, 
	      int _width, int _height):
   DLD_TVObj (_name, pd), 
   TButton (TRect (1,1,0,0), _name.c_str(), cmOK, bfNormal),
   markers("[]")
{
   height = _height + 1;
   width = _width - (hotk) * 2 + 5;
   lenWidth.setMin(width);
   lenHeight.setMin(height);
   lenHeight.setPref(height);
//   lenWidth.setPref(width*1000);
//   lenHeight.setPref(height*1000);

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "button "<< dld_name 
	  << " (" << width << "," << height 
	  << ") constructed.\n" ;
   DLDdbg.flush ();
#endif
   dld_title = dld_name.c_str();
}

DLD_TVButton::
~DLD_TVButton ()
{
#ifdef DEBUG
   DLDdbg << "~button " << dld_name << "\n";
   DLDdbg.flush ();
#endif
}

void DLD_TVButton::
create ()
{
#ifdef DEBUG
   DLDdbg << "button create" << dld_name << "\n";
#endif
   DLD_Obj::create();
}

TPalette& DLD_TVButton::getPalette() const
{
   static TPalette palette (cpTVBDis, sizeof(cpTVBDis)-1);

   if(is_disabled) {      
      return palette;
   }
   else return TButton::getPalette();
}

void DLD_TVButton::
activate ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "button " << dld_name << "activate\n";
#endif

   DLD_TVObj::activate ();
}

void DLD_TVButton::
press ()
{
   activate ();
}

void DLD_TVButton::
changeBounds( const TRect& bounds ) {    
   TButton::changeBounds(bounds); 

#ifdef DEBUG  
   DLDdbg << "button changeBounds(" << bounds.a.x << "," << bounds.a.y << ")"
	<< "(" << bounds.b.x << "," << bounds.b.y << ")"
	<< endl;      
#endif
};


void DLD_TVButton::
calcBounds(TRect& bounds, TPoint)
{
   bounds = geom;
}

void DLD_TVButton::draw()
{
    drawState(False);
}

void DLD_TVButton::drawState(Boolean down)
{
   ushort cButton, cShadow;
   char   ch = ' ';
   TDrawBuffer b;

   if( (state & sfDisabled) != 0 )
      cButton = getColor(0x0404);
   else
   {
      cButton = getColor(0x0501);
      if( (state & sfActive) != 0 )
	 if( (state & sfSelected) != 0 )
	    cButton = getColor(0x0703);
	 else if( amDefault )
	    cButton = getColor(0x0602);
   }
   cShadow = getColor(0x8);
   int s = size.x-1;
//   int T = size.y / 2 - 1;

#ifdef DEBUG
   DLDdbg << "button drawState y <= " << size.y-2 << endl << flush;
#endif
   Boolean center=True;
   int l = strlen(dld_title);
   int p = 0, j = 0;
   int i = 0;

   for( int y = 0; y <= size.y-2; y++ ) {      
      if(dld_title) {
	 int begin = 0;
	 
	 b.moveChar( 0, ' ', cButton, size.x );
	 b.putAttribute( 0, cShadow );
	 if( down ) {
	    b.putAttribute( 1, cShadow );
	    ch =  ' ';
	    begin = 3;
	 }
	 else {
	    b.putAttribute( s, cShadow );
	    if( showMarkers == True )
	      ch = ' ';
	    else {
	       if( y == 0 )
		 b.putChar( s, shadows[0] );
	       else
		 b.putChar( s, shadows[1] );
	       ch = shadows[2];
	    }
	    begin =  2;
	 }
	 
	 //	    b.moveChar(0, ' ', cButton, s);
	 if (p < l) {
	    if (dld_title[p] == 3) {
	       center = True;
	       ++p;
	    }
	    i = p;
	    do {
	       j = p;
	       while ((p < l) && (dld_title[p] == ' '))
		 ++p;
	       while ((p < l) && (dld_title[p] != ' ') && (dld_title[p] != '\n'))
		 ++p;
	    } while ((p < l) && (p < i + s) && (dld_title[p] != '\n'));
	    if (p > i + s)
	      if (j > i)
		p = j;
	    else
	      p = i + s;
	    if (center == True)
	      j = begin + (s - p + i) / 2 ;
	    else
	      j = begin;
	    
	    char txt[p-i+1];
	    memcpy(txt, &dld_title[i], (p-i));
	    txt[p-i] = '\0';
	    
	    b.moveCStr(j, txt, cButton);
	    
	    while ((p < l) && (dld_title[p] == ' '))
	      p++;
	    
	    if ((p < l) && (dld_title[p] == '\n')) {
	       //		  center = False;
	       p++;
	    }
	 }
	    
//	    b.moveCStr(0, y, s, 1);

	 if( showMarkers == True && !down )
	   {
	      int scOff;
	      if( (state & sfSelected) != 0 )
		scOff = 0;
	      else if( amDefault )
		scOff = 2;
	      else
		scOff = 4;
	      b.putChar( 0, specialChars[scOff] );
	      b.putChar( s, specialChars[scOff+1] );
	      b.putChar( 1, markers[0] );
	      b.putChar( s-1, markers[1] );
	   }
	 writeLine( 0, y, size.x, 1, b );
      }

      if( showMarkers && !down ) {
	 b.putChar( 1, markers[0] );
	 b.putChar( s-1, markers[1] );
      }
      writeLine( 0, y, size.x, 1, b );
   }
   b.moveChar( 0, ' ', cShadow, 2 );
   b.moveChar( 2, ch, cShadow, s-1 );
   writeLine( 0, size.y-1, size.x, 1, b );
}

void DLD_TVButton::handleEvent( TEvent& event )
{
   if(is_disabled)
      return;

   TPoint mouse;
   TRect clickRect;

   clickRect = getExtent();
   clickRect.a.x++;
   clickRect.b.x--;
   clickRect.b.y--;

   if( event.what == evMouseDown )
   {
      mouse = makeLocal( event.mouse.where );
      if( !clickRect.contains(mouse) )
	 clearEvent( event );
   }
   if (flags & bfGrabFocus)
      TView::handleEvent(event);

   char c = hotKey( dld_title );
   switch( event.what )
   {
   case evMouseDown:
      if ((state &  sfDisabled) == 0)
      {
	 clickRect.b.x++;
	 Boolean down = False;
	 do  {
	    mouse = makeLocal( event.mouse.where );
	    if( down != clickRect.contains( mouse ) )
	    {
	       down = Boolean( !down );
	       drawState( down );
	    }
	 } while( mouseEvent( event, evMouseMove ) );
	 if( down )
	 {
	    press();
	    drawState( False );
	 }
      }
      clearEvent( event );
      break;

   case evKeyDown:
      if( event.keyDown.keyCode == getAltCode(c) ||
	  ( owner->phase == phPostProcess &&
	    c != 0 &&
	    toupper(event.keyDown.charScan.charCode) == c
	     ) ||
	  ( (state & sfFocused) != 0 &&
	    event.keyDown.charScan.charCode == ' '
	     )
	 )
      {
	 press();
	 clearEvent( event );
      }
      break;

   case evBroadcast:
      switch( event.message.command )
      {
      case cmDefault:
	 if( amDefault && !(state & sfDisabled) )
	 {
	    press();
	    clearEvent(event);
	 }
	 break;

      case cmGrabDefault:
      case cmReleaseDefault:
	 if( (flags & bfDefault) != 0 )
	 {
	    amDefault = Boolean(event.message.command == cmReleaseDefault);
	    drawView();
	 }
	 break;

      case cmCommandSetChanged:
	 setState(sfDisabled,Boolean(!commandEnabled(command)));
	 drawView();
	 break;
      }
      break;
   }

}


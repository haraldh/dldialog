/******************************************************************************
**
** $Id: dld_text.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#define Uses_TRect

#include "dld_tvlib.h"
#include "dld_text.h"
#include "dld_dialog.h"
#include <iostream.h>
#include <string.h>

DLD_TVText :: 
DLD_TVText (const string& name, DLD_TVDialog * pd, 
	    int _width, int _height):
   DLD_TVObj (name, pd),
   TStaticText (TRect (0, 0, _width, _height), name.c_str())
{
   lenWidth.setMin(_width);
   lenHeight.setMin(_height);
   lenWidth.setPref(_width);
   lenHeight.setPref(_height);
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "text h=" << _height << " w=" << _width << "\n";
#endif
}

DLD_TVText::
~DLD_TVText ()
{
#ifdef DEBUG
   DLDdbg << "~text " << dld_name << "\n";
#endif
}

void DLD_TVText::
create()
{
   DLD_Obj::create();
}

void DLD_TVText::
changeBounds( const TRect& bounds ) {    
   TStaticText::changeBounds(bounds); 
};

void DLD_TVText::
calcBounds(TRect& bounds, TPoint)
{
   bounds = geom;
}

void DLD_TVText::draw()
{
   uchar color;
   Boolean center;
   int i, j, l, p, y;
   TDrawBuffer b;
   char s[1024];

   color = getColor(1);
   getText(s);
   l = strlen(s);
   p = 0;
   y = 0;
   center = False;
   while (y < size.y)
   {
      b.moveChar(0, ' ', color, size.x);
      if (p < l)
      {
	 if (s[p] == 3)
	 {
	    center = True;
	    ++p;
	 }
	 i = p;
	 do {
	    j = p;
	    while ((p < l) && (s[p] == ' '))
	       ++p;
	    while ((p < l) && (s[p] != ' ') && (s[p] != '\n'))
	       ++p;
	 } while ((p < l) && (p < i + size.x) && (s[p] != '\n'));
	 if (p > i + size.x)
	    if (j > i)
	       p = j;
	    else
	       p = i + size.x;
	 if (center == True)
	    j = (size.x - p + i) / 2 ;
	 else
	    j = 0;
	 b.moveBuf(j, &s[i], color, (p - i));
	 while ((p < l) && (s[p] == ' '))
	    p++;
	 if ((p < l) && (s[p] == '\n'))
	 {
	    center = False;
	    p++;
	 }
      }
      writeLine(0, y++, size.x, 1, b);
   }
}

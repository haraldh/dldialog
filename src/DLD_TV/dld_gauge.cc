/******************************************************************************
**
** $Id: dld_gauge.cc,v 1.1 2001/03/14 02:33:18 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#define Uses_TDrawBuffer
#define Uses_TColor
#define Uses_TEvent

#include "dld_tvlib.h"
#include "dld_gauge.h"

#include <tvision/tv.h>
#include <iostream.h>
#include <stdio.h>

#define cpTVGauge "\x0A\x0B\x0C\x0D\x0E\x0E\x0E\x0F"

DLD_TVGauge::
DLD_TVGauge (const string& _name, DLD_TVDialog *_pd) : 
   DLD_TVObj(_name, _pd),
   TView(TRect(0,0,7,1)),
   progress(0)	 
{   
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "gauge " << dld_name << "\n";;
#endif
   
   options |= ofFramed;
   options &= ~ofSelectable;

   lenWidth.setMin(8);

   lenHeight.setMin(3);
   lenHeight.setPref(3);
}

DLD_TVGauge::
~DLD_TVGauge ()
{
#ifdef DEBUG
   DLDdbg << "~gauge " << dld_name << "\n";
#endif
   char istr[512];
   sprintf(istr, "%d", progress);
   varvalue = istr;
   activate();
}

void DLD_TVGauge::
draw()
{
   if (progress >= 0 && progress <= 100) {
      ushort cProgress, cNProgress;
      TDrawBuffer b;
      
      cNProgress = getColor(10);
      cProgress = getColor(0x503);
      
      // Numberx of progress chars
      int nc = (size.x-6) * progress / 100;
      
      char pstr[5];
      sprintf(pstr, "% 4d%%", progress);
      for(int i=0; i < 5 ; i++)
	 b.moveChar(i, pstr[i], getColor(8), 1);
      
      b.moveChar( 5, ' ', getColor(8), 1);
      b.moveChar( 6, '#', cProgress, nc);
      b.moveChar( nc + 6, '.', cNProgress, size.x - nc - 6);
      
      // Write size.y line with chars
      writeLine( 0, 0, size.x, size.y, b );
   }
}

void DLD_TVGauge::
changeBounds( const TRect& bounds ) {    
   TRect nb(bounds);
   nb.grow(-1,-1);
   TView::changeBounds(nb); 
}

TPalette& DLD_TVGauge::getPalette() const
{
   static TPalette palette (cpTVGauge, sizeof(cpTVGauge)-1);
   return palette;
}

void DLD_TVGauge::
create() 
{
   if(varname.length()) {
      string val(dialog->get_env(varname));
      sscanf(val.c_str(), "%d", &progress);
      draw();
   }
   DLD_Gauge::create();
   DLD_Obj::create();
}

void DLD_TVGauge::
set_progress(int _p)
{
   if((_p >= 0 ) && (_p <= 100)) {
      progress = _p;
      char istr[512];
      sprintf(istr, "%d", progress);
      varvalue = istr;
      // DLD_Obj is without exit
      DLD_Obj::activate();
      draw();
   }
   if (_p < 0) {
      if(is_exit())
      {
	 progress = _p;
	 // Generate Dialog exit event
	 TEvent te;
	 te.what = evCommand;
	 te.message.command = cmClose;
	 te.message.infoPtr = 0;
	 putEvent (te);  
      }
   }
}

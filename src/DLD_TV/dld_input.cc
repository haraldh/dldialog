/******************************************************************************
**
** $Id: dld_input.cc,v 1.1 2001/03/14 02:33:18 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#define Uses_TFilterValidator
#define Uses_TEvent
#define Uses_TKeys
#include "dld_input.h"
#include "dld_dialog.h"
#include <tvision/tv.h>
#include <stdio.h>

DLD_TVInput::DLD_TVInput(const string& name, DLD_TVDialog *pd) :
   DLD_TVObj(name, pd),
   TInputLine(TRect(0,0,10,1), 1024)
{
   height = 1;
   width = 3;
   lenWidth.setMin(width);
   lenHeight.setMin(height);   
   lenHeight.setPref(height);   
   isPasswd=false;
   TInputLine::maxLen = 1023;
   eventMask |= evBroadcast;
}

DLD_TVInput::~DLD_TVInput()   
{
   varvalue = TInputLine::data;
   dia = 0;
   activate();
}

void DLD_TVInput::create()
{
   strncpy(TInputLine::data, dia->get_env(varname).c_str(), 
	   TInputLine::maxLen);
   int mlen = max(maxLen, dia->get_env(varname).length());
   TInputLine::data[mlen]=0;
   DLD_Obj::create();
}

void DLD_TVInput::set_length(int len)
{
   width = len+2;
   TInputLine::maxLen = len;
   lenWidth.setMin(width);
   lenWidth.setPref(width);
}

void DLD_TVInput::set_ip(bool flag)
{
   if(!flag)
      return;

   width = 18;
   lenWidth.setMin(width);
   lenWidth.setPref(width);

   setValidator(new DLD_TVIPValidator());
}

void DLD_TVInput::set_numeric(bool flag)
{
   if(!flag)
      return;

   setValidator(new TFilterValidator("01234567890"));
}

void DLD_TVInput::set_passwd(bool flag)
{
   if(!flag)
      return;
   isPasswd = flag;
}

void DLD_TVInput::draw()
{
   if(!isPasswd) {
      TInputLine::draw();
      return;
   }
   else {
      int l, r;
      TDrawBuffer b;
      
      uchar color = (state & sfFocused) ? getColor( 2 ) : getColor( 1 );
      
      b.moveChar( 0, ' ', color, size.x );
      char buf[256];
      int i;
      for(i = 0; (i < size.x - 2) && data[firstPos+i]; i++)
	 buf[i] = '*';

      buf[i] = 0;

      buf[size.x - 2 ] = EOS;
      b.moveStr( 1, buf, color );
      
      if( canScroll(1) )
	 b.moveChar( size.x-1, '\x10', getColor(4), 1 );
      if( (state & sfSelected) != 0 )
      {
	 if( canScroll(-1) )
            b.moveChar( 0, '\x11', getColor(4), 1 );
	 l = selStart - firstPos;
	 r = selEnd - firstPos;
	 l = max( 0, l );
	 r = min( size.x - 2, r );
	 if (l <  r)
            b.moveChar( l+1, 0, getColor(3), r - l );
      }
      writeLine( 0, 0, size.x, size.y, b );
      setCursor( curPos-firstPos+1, 0);
   }
}

Boolean DLD_TVInput::canScroll( int delta )
{
    if( delta < 0 )
        return Boolean( firstPos > 0 );
    else
        if( delta > 0 )
            return Boolean( (int)strlen(data) - firstPos + 2 > size.x );
        else
            return False;
}

void DLD_TVInput::handleEvent(TEvent& event)
{
   if( (state & sfSelected) != 0 )
      switch (event.what)
      {
      case evBroadcast:
	 switch(event.message.command)
	 {
	 case cmDefault:
	    activate();
	    break;
	 }
	 break;
      }
   TInputLine::handleEvent(event);
}

DLD_TVIPValidator::DLD_TVIPValidator()
{
   regcomp(&accept, "^[0-2]?[0-9]?[0-9]?\\.[0-2]?[0-9]?[0-9]?\\."
	   "[0-2]?[0-9]?[0-9]?\\.[0-2]?[0-9]?[0-9]?$", REG_NOSUB|REG_EXTENDED);

   regcomp(&correct, "^[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\."
	   "[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]$", REG_NOSUB|REG_EXTENDED);

}

DLD_TVIPValidator::~DLD_TVIPValidator()
{
   regfree(&accept);
   regfree(&correct);
}


Boolean DLD_TVIPValidator::isValid(const char* s)
{
   int num[4], i;
   
   if(sscanf(s, "%d.%d.%d.%d", &num[0], &num[1], &num[2], &num[3]) != 4)
      return False;

   for(i=0; i<4; i++) {
      if(num[i] < 0 || num[i] > 255) 
	 return False;
   }
   
   return (Boolean)(regexec(&correct, s, 0, 0, 0) == 0);
}

Boolean DLD_TVIPValidator::isValidInput(char* s, Boolean)
{
   if(strlen(s) == 0) {
      strcpy(s, "0.0.0.0");
      return True;
   }

   return (Boolean)(regexec(&accept, s, 0, 0, 0) == 0);
}


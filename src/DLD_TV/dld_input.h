/******************************************************************************
**
** $Id: dld_input.h,v 1.1 2001/03/14 02:33:18 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_TVINPUT_H
#define DLD_TVINPUT_H

#include <sys/types.h>
#include <regex.h>

#define Uses_TInputLine
#define Uses_TValidator

#include "../dld_input.h"
#include "dld_tvobj.h"

#include <tvision/tv.h>

/**
 * Abstract Interface
 * @short Abstract Interface
 * @author Harald Hoyer <HarryH@Royal.Net>
 */
class DLD_TVInput : public DLD_TVObj, public DLD_Input, public TInputLine
{
public:

   DLD_TVInput(const string& name, DLD_TVDialog *parent);
   /// Destructor.
   ~DLD_TVInput();

   void create() ;

   void changeBounds( const TRect& bounds ) { 
      TInputLine::changeBounds(bounds);
   };

   void calcBounds(TRect& bounds, TPoint) {
      bounds = geom;
   };

   void set_ip(bool);
   void set_passwd(bool);
   void set_numeric(bool);

   /** Set the maximal length of the input field
    * @param len the length
    */
   void set_length(int len);

   void draw();
   virtual void handleEvent(TEvent& event);

private:
   Boolean canScroll( int delta );

   bool isPasswd;
};

class DLD_TVIPValidator : public TValidator
{
public:
   DLD_TVIPValidator();
   ~DLD_TVIPValidator();

   Boolean isValid(const char* s);

   Boolean isValidInput(char* s, Boolean);

private:
   regex_t accept, correct;
};

#endif


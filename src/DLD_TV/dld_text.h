/******************************************************************************
**
** $Id: dld_text.h,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_TEXT_H
#define DLD_TEXT_H

#include "../dld_text.h"
#include "dld_tvobj.h"
#define Uses_TStaticText
#include <tvision/tv.h>

///
class DLD_TVText : public DLD_TVObj, public DLD_Text,
		   public TStaticText
{
public:
   ///
   DLD_TVText(const string& , DLD_TVDialog *, int width, int height);
   ///
   ~DLD_TVText();

   ///
   void create();

   void changeBounds( const TRect& bounds );

   void calcBounds(TRect& bounds, TPoint delta );
   virtual void draw();
};

#endif

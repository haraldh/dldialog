/******************************************************************************
**
** $Id: dld_form.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_FORM_H
#define DLD_FORM_H

#define Uses_TRect
#define Uses_TPoint
#define Uses_TStaticText

#include "../dld_form.h"
#include "dld_tvobj.h"
#include "dld_tvcontainer.h"
#include <tvision/tv.h>

///
class DLD_TVForm : public TView, public DLD_Form, public DLD_TVContainer
{
public:
   DLD_TVForm(const string& _name, DLD_TVApp *aptr, DLD_TVDialog *dia);

   ~DLD_TVForm();
   
   void create();

   void changeBounds( const TRect& bounds);

   void calcBounds(TRect& bounds, TPoint) { bounds = geom; };

   void setGeom(const TRect& _g);

   void insert(TView *p);

   void close_brace();

   void draw();

private:
   ///
   TStaticText *label;
};

#endif


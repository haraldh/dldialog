/******************************************************************************
**
** $Id: dld_tvcheck.h,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_TVCHECK_H
#define DLD_TVCHECK_H

#include "../dld_checkbutton.h"
#include "dld_dialog.h"
#include "dld_checklist.h"
#include <tvision/tv.h>

///
class DLD_TVCheckButton : public DLD_TVObj, 
			  public DLD_CheckButton
{
public:
   ///
   DLD_TVCheckButton(const string& name, DLD_TVDialog *pd);

   ///
   virtual ~DLD_TVCheckButton();

   ///
   void create() { DLD_Obj::create(); };

   void changeBounds( const TRect&) {};
   void calcBounds(TRect&, TPoint) {};
};

#endif

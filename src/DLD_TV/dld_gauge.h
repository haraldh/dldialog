/******************************************************************************
**
** $Id: dld_gauge.h,v 1.1 2001/03/14 02:33:18 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_GAUGE_H
#define DLD_GAUGE_H

#define Uses_TView
#include "../dld_gauge.h"
#include "dld_tvobj.h"
#include <tvision/tv.h>

///
class DLD_TVGauge : public DLD_TVObj, public DLD_Gauge, public TView
{
public:
   /// Constructor
   DLD_TVGauge(const string& name, DLD_TVDialog *pd);
   
   /// Destructor
   ~DLD_TVGauge();

   void create();

   void changeBounds( const TRect& bounds );

   void calcBounds(TRect& bounds, TPoint) { bounds = geom; };

   void draw();

   TPalette& getPalette() const;

   void set_progress(int p);

private:
   /// The progress in percent to display
   int progress;

};

#endif

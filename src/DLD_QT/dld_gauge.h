/******************************************************************************
**
** $Id: dld_gauge.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_QTGAUGE_H
#define DLD_QTGAUGE_H

#include "../dld_gauge.h"
#include "dld_qtobj.h"
#include <qwidget.h>
#include <qprogressbar.h>

/** The button class in qt style.
 *
 */
class DLD_QTGauge :  public QProgressBar, public DLD_QTObj, 
		     public DLD_Gauge
{
public:
   ///
   DLD_QTGauge(QWidget *_parent, const string& name, DLD_QTDialog *pd);
   ///
   virtual ~DLD_QTGauge();
   ///
   void create();
   void set_progress(int p);  
};

#endif

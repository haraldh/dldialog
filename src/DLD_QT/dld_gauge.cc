/******************************************************************************
**
** $Id: dld_gauge.cc,v 1.1 2001/03/14 02:33:12 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
!******************************************************************************/
#include "dld_qtlib.h"
#include "dld_gauge.h"
#include "dld_dialog.h"
#include <stdio.h>
#include <iostream.h>

DLD_QTGauge::DLD_QTGauge (QWidget *_parent, 
			    const string& name, DLD_QTDialog *pd):
   QProgressBar (_parent),
   DLD_QTObj (name, pd)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "gauge " << dld_name << flush;
#endif
//   setMinimumWidth (sizeHint ().width ());
   setFixedHeight (sizeHint ().height ());
   fixed_height = true;

#ifdef DEBUG
   DLDdbg << " constructed." << endl << flush;
#endif
}

DLD_QTGauge::
~DLD_QTGauge ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "gauge deleted\n";
#endif
   activate();
}

void DLD_QTGauge::
create ()
{
   setTotalSteps(100);
   if(varname.length()) {
      int progress;
      string val(dialog->get_env(varname));
      sscanf(val.c_str(), "%d", &progress);
      set_progress(progress);
   }
   DLD_Obj::create();
   DLD_Gauge::create();
}

void DLD_QTGauge::
set_progress (int _p)
{
   static int oldp = 0;
   if ( (_p >= 0) && (_p <= 100) ) {
      char istr[512];
      sprintf(istr, "%d", _p);
      varvalue = istr;
      if (oldp > _p) {
	 setUpdatesEnabled( FALSE );
	 reset();
	 setProgress(_p);
	 setUpdatesEnabled( TRUE );
	 repaint();
      }
      else 
	setProgress(_p);
      oldp = _p;
      // DLD_Obj is without exit
      DLD_Obj::activate();
   }
   
   if (_p < 0) {
      if(is_exit())
      {
	 pardia->done(0);
      }
   }
}

/******************************************************************************
**
** $Id: dld_row.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_row.h"
#include <iostream.h>
#include <qfontmetrics.h> 

DLD_QTRow:: 
DLD_QTRow (QWidget *_parent, const string& _name, DLD_QTApp *aptr, 
	   DLD_QTDialog *dia) :
   QGroupBox (convstr(_name).c_str(), _parent),
   QHBoxLayout ((QGroupBox *) this, 0, QT_BORDER),
   DLD_QTObj (_name, dia),
   DLD_QTContainer(_name, aptr, dia),
   dld_cols(0),
   dld_rows(0)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "row ";
#endif
   if (dld_name.length() == 0)
      setFrameStyle (NoFrame);
   else {
#if QT_VERSION < 200
      basicManager()->setBorder(20);
#endif
//     dld_rows = 1;
   }

   qwidget = this;
   fixed_width = fixed_height = true;
}

DLD_QTRow::
~DLD_QTRow ()
{
}

void DLD_QTRow::
insert (QWidget * w, DLD_QTObj *obj)
{
   QHBoxLayout::addWidget (w, AlignLeft|AlignVCenter);
   qtobjs[dld_cols] = obj;
   qwidgets[dld_cols] = w;
   dld_cols++;
}

void DLD_QTRow::
create (void)
{
   int nullanz=0, sum=0;   
   for(int i = 0; i < dld_cols; i++)
   {
      if(!qtobjs[i])
	 continue;
      int p = qtobjs[i]->obj_widthP;

      if (qtobjs[i]->obj_heightP)
	 fixed_height = false;

      if(p) {
	 sum += p;
	 fixed_width = false;
      }
      else
	 nullanz++;
   }
   sum = (sum && (sum < 100)) ? 100 - nullanz : nullanz;
   for(int i = 0; i < dld_cols; i++)
   {
      if(!qtobjs[i])
	 continue;
      int p = qtobjs[i]->obj_widthP;
      if(p)
	 setStretchFactor(qwidgets[i], p);
      else {
	 if(qtobjs[i]->fixed_width)
	    setStretchFactor(qwidgets[i], 0);
	 else
	    setStretchFactor(qwidgets[i], sum / nullanz);
      }
   }

   DLD_QTContainer::create ();
   QHBoxLayout::activate ();
}

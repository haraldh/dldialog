/******************************************************************************
**
** $Id: dld_col.cc,v 1.1 2001/03/14 02:33:08 saturn_de Exp $
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
#include "dld_col.h"
#include <iostream.h>
#include <qfontmetrics.h> 

DLD_QTCol:: 
DLD_QTCol (QWidget *_parent, const string& _name,
	   DLD_QTApp *aptr, DLD_QTDialog *dia) :
   QGroupBox (convstr(_name).c_str(), _parent),
   QVBoxLayout ((QGroupBox *) this, 0, QT_BORDER/2),
   DLD_QTObj (_name, dia),
   DLD_QTContainer(_name, aptr, dia),
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
   }

//   setRowStretch(0, 1);

   qwidget = this;
   fixed_width = fixed_height = true;
}

DLD_QTCol::
~DLD_QTCol ()
{
}

void DLD_QTCol::
insert (QWidget * w, DLD_QTObj *obj)
{
   QVBoxLayout::addWidget (w, AlignLeft|AlignVCenter);
   qtobjs[dld_rows] = obj;
   qwidgets[dld_rows] = w;
   dld_rows++;
}

void DLD_QTCol::
create (void)
{
   int nullanz=0, sum=0;
   for(int i = 0; i < dld_rows; i++)
   {
      if(!qtobjs[i])
	 continue;
      int p = qtobjs[i]->obj_heightP;

      if (qtobjs[i]->obj_heightP)
	 fixed_width = false;

      if(p) {
	 sum += p;
	 fixed_height = false;
      }
      else
	 nullanz++;
   }
   sum = (sum && (sum < 100)) ? 100 - nullanz : nullanz;
   for(int i = 0; i < dld_rows; i++)
   {
      if(!qtobjs[i])
	 continue;
      int p = qtobjs[i]->obj_heightP;
      if(p)
	 setStretchFactor(qwidgets[i], p);
      else {
	 if(qtobjs[i]->fixed_height)
	    setStretchFactor(qwidgets[i], 0);
	 else
	    setStretchFactor(qwidgets[i], sum / nullanz);
      }
   }
   DLD_QTContainer::create ();
   QVBoxLayout::activate ();
}

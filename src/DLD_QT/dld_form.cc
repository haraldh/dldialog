/******************************************************************************
**
** $Id: dld_form.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_form.h"
#include <iostream.h>
#include <qfontmetrics.h> 

DLD_QTForm:: 
DLD_QTForm (QWidget *_parent, const string& _name, DLD_QTApp *aptr, 
	   DLD_QTDialog *dia) :
   QGroupBox (convstr(_name).c_str(), _parent),
   QHBoxLayout ((QGroupBox *) this, QT_BORDER),
   DLD_QTObj (_name, dia),
   DLD_QTContainer(_name, aptr, dia),
   dld_cols(0),
   dld_rows(0)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "row ";
#endif
   if (_name.length() == 0)
      setFrameStyle (NoFrame);
   else
#if QT_VERSION < 200
      basicManager()->setBorder(20);
#endif
//     dld_rows = 1;
//   setRowStretch(0, 1);

//   setMargin(10);
   qwidget = this;
   fixed_width = fixed_height = true;
}

DLD_QTForm::
~DLD_QTForm ()
{
}

void DLD_QTForm::
insert (QWidget * w, DLD_QTObj *obj)
{
   QHBoxLayout::addWidget (w, AlignCenter);
   qtobjs[dld_rows] = obj;
   qwidgets[dld_rows] = w;
   dld_cols++;
}

void DLD_QTForm::
create (void)
{
   int nullanz=0, sum=0;
   for(int i = 0; i < dld_rows; i++)
   {
      if(!qtobjs[i])
	 continue;
      int p = qtobjs[i]->obj_heightP;
      if(p)
	 sum += p;
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
   QHBoxLayout::activate ();
}

/******************************************************************************
**
** $Id: dld_check.h,v 1.1 2001/03/14 02:33:07 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#ifndef DLD_QTCHECKBUTTON_H
#define DLD_QTCHECKBUTTON_H

#include "../dld_checkbutton.h"
#include "dld_qtlib.h"
#include "dld_qtobj.h"
#include <qchkbox.h> 

/** The check class in qt style.
 *
 */
class DLD_QTCheckButton : public QCheckBox, public DLD_CheckButton, 
			  public DLD_QTObj
{
   Q_OBJECT;
public:
   ///
   DLD_QTCheckButton(QWidget *_parent, const string& name, DLD_QTDialog *pd);

   ///
   virtual ~DLD_QTCheckButton();
   
   ///
   void create();

signals:
   void signal_cbpress();

///
public slots:
   void slot_activate(bool);
   
};

#endif

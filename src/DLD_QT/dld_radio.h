/******************************************************************************
**
** $Id: dld_radio.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_RADIO_H
#define DLD_RADIO_H

#include "../dld_radiobutton.h"
#include "dld_qtlib.h"
#include "dld_qtobj.h"
#include <qradiobt.h>
#include <qwidget.h>

/** The radiobutton class in qt style, to use within @ref DLD_Radiolist.
 *
 */
class DLD_QTRadioButton : public QRadioButton, public DLD_QTObj, 
			  public DLD_RadioButton
{
  Q_OBJECT;

public:
   ///
   DLD_QTRadioButton(int num, QWidget *_parent, 
		     const string& name, DLD_QTDialog *pd);
   
   ///
   virtual ~DLD_QTRadioButton();
   
   ///
   void create();

signals:
   void signal_rbpress(int num);

///
public slots:
   void slot_activate(bool);

private:
   int mynum;
};

#endif

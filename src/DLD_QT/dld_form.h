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

#include "../dld_form.h"
#include "dld_qtcontainer.h"
#include <qlayout.h>
#include <qgrpbox.h> 
#include <map>

class DLD_QTDialog;
class DLD_QTApp;

/** A container for other dldialog elements, that orders these in a row.
 *
 */
class DLD_QTForm : public QGroupBox, public QHBoxLayout, 
		  public DLD_QTContainer, public DLD_Form
{
public:
   ///
   DLD_QTForm(QWidget *_parent, const string& _name,
	     DLD_QTApp *aptr, DLD_QTDialog *dia);

   ///
   virtual ~DLD_QTForm();

   ///
   void insert(QWidget *w, DLD_QTObj *obj);

   ///
   void create();

   void close_brace() { create(); };

private:
   int dld_cols, dld_rows;
   map<int, DLD_QTObj*> qtobjs;
   map<int, QWidget*> qwidgets;
};

#endif

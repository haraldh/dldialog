/******************************************************************************
**
** $Id: dld_row.h,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#ifndef DLD_ROW_H
#define DLD_ROW_H

#include "../dld_row.h"
#include "dld_qtcontainer.h"
#include <qlayout.h>
#include <qgrpbox.h> 
#include <map>
class DLD_QTDialog;
class DLD_QTApp;

/** A container for other dldialog elements, that orders these in a row.
 *
 */
class DLD_QTRow : public QGroupBox, public QHBoxLayout, 
		  public DLD_QTContainer, public DLD_Row
{
public:
   ///
   DLD_QTRow(QWidget *_parent, const string& _name,
	     DLD_QTApp *aptr, DLD_QTDialog *dia);

   ///
   virtual ~DLD_QTRow();

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

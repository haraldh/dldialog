/******************************************************************************
**
** $Id: dld_col.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_COL_H
#define DLD_COL_H

#include "../dld_col.h"
#include "dld_qtcontainer.h"
#include <qlayout.h>
#include <qgrpbox.h> 
#include <map>

class DLD_QTDialog;
class DLD_QTApp;

/** A container for other dldialog elements, that orders these in a column.
 *
 */
class DLD_QTCol : public QGroupBox, public QVBoxLayout, 
		  public DLD_QTContainer, public DLD_Col
{
public:
   ///
   DLD_QTCol(QWidget *_parent, const string& _name, 
	     DLD_QTApp *aptr, DLD_QTDialog *dia);

   ///
   virtual ~DLD_QTCol();

   ///
   void insert(QWidget *w, DLD_QTObj *obj);

   ///
   void create();

   void close_brace() { create(); };

private:
   int dld_rows;
   map<int, DLD_QTObj*> qtobjs;
   map<int, QWidget*> qwidgets;
};

#endif

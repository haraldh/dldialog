/******************************************************************************
**
** $Id: dld_checklist.h,v 1.1 2001/03/14 02:33:08 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#ifndef DLD_QTCHECKLIST_H
#define DLD_QTCHECKLIST_H

#include "../dld_checklist.h"
#include "dld_qtlib.h"
#include "dld_qtobj.h"
#include <qbttngrp.h> 
#include <qlayout.h>

/** The checklist in qt style.
 *
 */
class DLD_QTCheckList : public QButtonGroup, public DLD_CheckList, 
			public DLD_QTObj
{
   Q_OBJECT;
public:
   ///
   DLD_QTCheckList(QWidget *_parent, const string& name, DLD_QTDialog *pd);

   ///
   virtual ~DLD_QTCheckList();

   ///
   void create();

   /** Adds a checkbutton to the checklist.
    * @param name The text of the item
    * @return ptr to item
    */
   DLD_CheckButton *checkbutton(const string&);

   /** Indicates the beginning of a new block
    *
    * Can be used to reserve space for children.
    */
   void open_brace() {};

   /** Indicates the end of a block.
    *
    * Can be used to collect all children.
    */
   void close_brace() {};

public slots:
   void slot_cbpress ();

private:
   void update_var();

   ///
   int count;

   QVBoxLayout *topLayout;
};

#endif

/******************************************************************************
**
** $Id: dld_combobox.h,v 1.1 2001/03/14 02:33:08 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#ifndef DLD_QTCOMBOBOX_H
#define DLD_QTCOMBOBOX_H

#include "../dld_combobox.h"
#include "dld_qtlib.h"
#include "dld_qtobj.h"
#include "dld_comboitem.h"
#include <qcombobox.h>
#include <qptrdict.h>
#include <map>
/**  The combobox class in qt style.
 * Ordering of QTObj and ListBox is important, because ListBox wants to delete
 * our children.
 */

class DLD_QTComboBox : public QComboBox, public DLD_ComboBox, 
		      public DLD_QTObj
{
   Q_OBJECT;
public:
   ///
   DLD_QTComboBox(QWidget *_parent, 
		  const string& name, DLD_QTDialog *pd);
   ///
   virtual ~DLD_QTComboBox();
   
   ///
   DLD_ComboItem *comboitem(const string& name);
   ///
   void create();
   
   /** Indicates the beginning of a new block
    *
    * Can be used to reserve space for children.
    */
   virtual void open_brace() {};
   
   /** Indicates the end of a block.
    *
    * Can be used to collect all children.
    */
   virtual void close_brace() {};

public slots:
   void slot_activated(int);
   
protected:
   ///
   typedef DLD_QTComboItem *DLD_QTComboItem_PTR;
   map<int, DLD_QTComboItem_PTR> citems;
};

#endif

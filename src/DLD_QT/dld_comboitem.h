/******************************************************************************
**
** $Id: dld_comboitem.h,v 1.1 2001/03/14 02:33:08 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de>
**
******************************************************************************/
#ifndef DLD_QTCOMBOITEM_H
#define DLD_QTCOMBOITEM_H

#include "../dld_comboitem.h"
#include "dld_qtobj.h"

/** .
 *
 */
class DLD_QTComboItem : public DLD_QTObj, public DLD_ComboItem
{
public:
   ///
   DLD_QTComboItem(const string& name, DLD_QTDialog *pd);
   ///
   virtual ~DLD_QTComboItem();
   void create() {DLD_Obj::create();};
};

#endif

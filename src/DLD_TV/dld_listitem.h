/******************************************************************************
**
** $Id: dld_listitem.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_LISTITEM_H
#define DLD_LISTITEM_H

#include "../dld_listitem.h"
#include "dld_tvobj.h"

/**
 * Abstract Interface
 * @short Abstract Interface
 * @author Harald Hoyer <dldialog@parzelle.de>
 */
class DLD_TVListItem : public DLD_TVObj, public DLD_ListItem {
public:

   DLD_TVListItem(const string& name, DLD_TVDialog *parent);

   /// Destructor.
   virtual ~DLD_TVListItem();

   /// empty 
   void create() { DLD_Obj::create(); };

   /// empty 
   void changeBounds(const TRect&) {};

   /// empty 
   void calcBounds(TRect&, TPoint) {};

};

#endif

/******************************************************************************
**
** $Id: dld_checklist.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_TVCHECKLIST_H
#define DLD_TVCHECKLIST_H

#define Uses_TCheckBoxes
#define Uses_TLabel

#include "../dld_checklist.h"
#include "dld_tvobj.h"

#include <tvision/tv.h>

///
class DLD_TVCheckButton;

class DLD_TVCheckList : public DLD_TVObj, 
			public DLD_CheckList, 
			public TCheckBoxes
{
public:
   ///
   DLD_TVCheckList(const string& name, DLD_TVDialog *pd);
   ///
   virtual ~DLD_TVCheckList();

   /** Indicates the beginning of a new block
    *
    * Can be used to reserve space for children.
    */
   void open_brace() {};

   /** Indicates the end of a block.
    *
    * Can be used to collect all children.
    */
   void close_brace();

   /** Indicates the creation.
    *
    */
   void create();
   
   DLD_CheckButton *checkbutton(const string& name);

   void changeBounds( const TRect& bounds );
   void calcBounds(TRect& bounds, TPoint delta );

   void press(int item);

protected:
   void update_var();
   ///
   TSItem *item;

   ///
   DLD_TVCheckButton *check[32];

   ///
   int check_ctr;

   ///
   TLabel *label;
};

#endif

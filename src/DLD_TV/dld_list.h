/******************************************************************************
**
** $Id: dld_list.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_LIST_H
#define DLD_LIST_H

#define Uses_TListBox
#define Uses_TScrollBar
#define Uses_TStringCollection
#define Uses_TLabel

#include "../dld_list.h"
#include "dld_tvobj.h"
#include "dld_listitem.h"
#include <tvision/tv.h>
#include <vector>

class DLD_ScrollBar : public TScrollBar {
public:  
   DLD_ScrollBar(const TRect a, DLD_TVDialog *pd);
   void changeBounds( const TRect&) { TScrollBar::changeBounds(geom);};
   void calcBounds(TRect& bounds, TPoint) {
      bounds = geom;
   };
   virtual void setGeom(const TRect& _g) { geom = _g; };
private:
   TRect geom;
};

///
class DLD_TVList : public DLD_TVObj, public DLD_List, 
		   public TListBox
{
public:
   ///
   DLD_TVList(const string& name, DLD_TVDialog *pd);
   ///
   ~DLD_TVList();
   
   ///
   void create();
   
   virtual void handleEvent(TEvent& event);

   void changeBounds( const TRect& bounds );
   
   void calcBounds(TRect& bounds, TPoint delta );
   
   DLD_ListItem * listitem (const string& = 0);
   
   /** Indicates the beginning of a new block
    *
    * Can be used to reserve space for children.
    */
   void open_brace();
   
   /** Indicates the end of a block.
    *
    * Can be used to collect all children.
    */
   void close_brace();

   void selectItem( short item );

protected:
   void update_var();
   char tag;

private:
   DLD_ScrollBar *aScrollBar;
   TStringCollection listcol;

   typedef DLD_TVListItem *DLD_TVListItem_Ptr;
   vector<DLD_TVListItem_Ptr>  childarray;
   typedef vector<DLD_TVListItem_Ptr>::iterator CI; 

   ///
   TLabel *label;
   unsigned int list_ctr;

   void ToggleItem(int item_no);
   void MarkAll();
   void UnMarkAll();
   void ToggleAll();
   bool was_double;
};

#endif

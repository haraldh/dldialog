/******************************************************************************
**
** $Id: dld_radiolist.h,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_RADIOLIST_H
#define DLD_RADIOLIST_H

#define Uses_TRadioButtons
#define Uses_TLabel

#include "../dld_radiolist.h"
#include "dld_tvobj.h"

#include <tvision/tv.h>

///
class DLD_TVRadioButton;

class DLD_TVRadioList : public DLD_TVObj, 
			public DLD_RadioList,
			public TRadioButtons
{
public:
   ///
   DLD_TVRadioList(const string& name, DLD_TVDialog *pd);
   ///
   virtual ~DLD_TVRadioList();

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

   void press( int item );
   void movedTo( int item );
   
   DLD_RadioButton *radiobutton(const string& name);

   void changeBounds( const TRect& bounds );
   void calcBounds(TRect& bounds, TPoint delta );

protected:

   void update_var();

   ///
   TSItem *item;

   ///
   DLD_TVRadioButton *radio[32];

   ///
   unsigned int radio_ctr;

   ///
   TLabel *label;
};

#endif

/******************************************************************************
**
** $Id: dld_tvradio.h,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_TVRADIO_H
#define DLD_TVRADIO_H

#include "../dld_radiobutton.h"
#include "dld_dialog.h"
#include "dld_radiolist.h"
#include <tvision/tv.h>

/** TV RadioButton implementation.
 */
class DLD_TVRadioButton : public DLD_TVObj, 
			  public DLD_RadioButton
{
public:
   /// Contructor.
   DLD_TVRadioButton(const string& name, DLD_TVDialog *pd);

   /// Destructor.
   virtual ~DLD_TVRadioButton();

   /// empty 
   void create() { DLD_Obj::create(); };

   /// empty 
   void changeBounds( const TRect&) {};

   /// empty 
   void calcBounds(TRect&, TPoint) {};
};
#endif

/******************************************************************************
**
** $Id: dld_dialog.h,v 1.1 2001/03/14 02:33:18 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_TVDIALOG_H
#define DLD_TVDIALOG_H

#define Uses_TDialog

#include "../dld_dialog.h"
#include "dld_tvobj.h"
#include "dld_tvcontainer.h"

#include <tvision/tv.h>

class DLD_TVApp;

///
class DLD_TVDialog: public TDialog, public DLD_TVContainer, 
		    public DLD_Dialog
{
public:
   ///
   DLD_TVDialog(const string& name, DLD_TVApp *aptr, const DLD_Out path);
   
  ///
   ~DLD_TVDialog();
   
   ///
   void create();

   void insert(TView *p);

   void changeBounds( const TRect& bounds );
   void calcBounds(TRect& bounds, TPoint delta );

   void close_brace() ;
   void handleEvent( TEvent& event );

private: 
   int oh, ow;
};

#endif

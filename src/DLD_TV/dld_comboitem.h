/******************************************************************************
**
** $Id: dld_comboitem.h,v 1.1 2001/03/14 02:33:14 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "../dld_comboitem.h"
#include "dld_tvobj.h"

/**
 * Abstract Interface
 * @short Abstract Interface
 * @author Harald Hoyer <HarryH@Royal.Net>
 */
class DLD_TVComboItem : public DLD_TVObj, public DLD_ComboItem {
public:
   DLD_TVComboItem(const string& name, DLD_TVDialog *parent, int _nr) : 
      DLD_TVObj(name, parent),
      number(_nr) {};

   void create() { DLD_Obj::create(); };
   
   void changeBounds( const TRect& ) {};
   
   void calcBounds(TRect& , TPoint ) {};
   
   int getNumber() { return number; };

private:
   int number;
};

/******************************************************************************
**
** $Id: dld_qtobj.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de>
**
******************************************************************************/

#include "dld_qtobj.h"
#include "dld_dialog.h"

string conname (const string& _str);

/// Constructor
DLD_QTObj::DLD_QTObj(const string& name, DLD_QTDialog *pd) : 
   dld_name(conname(name)),
   obj_widthP(0),
   obj_heightP(0),
   fixed_width(false),
   fixed_height(false),
   pardia(pd),
   app(0),
   isexit(false)
{
   set_dialog(pd);
}

DLD_QTObj::
~DLD_QTObj()
{
   DLDdbg << dld_name << " ~DLD_QTObj virtual destruktor" << endl;
}

void DLD_QTObj::activate()
{
   DLD_Obj::activate();

   if(is_exit() && pardia && is_created) {
      DLDdbg << dld_name << " exited Dialog" << endl;      
      pardia->done(0);
   }
}

string conname (const string& _str)
{
   string str = convstr (_str);
   string::size_type i;

   while ((i = str.find("\t")) != string::npos) {
      str.replace(i, 1, " ");
      int lp = i - str.rfind("\n", i);
      for(int j = 7 - (lp%8); j > 0; j--) {
         str.insert(i, " ");
      }
   }

   return str;
}


/******************************************************************************
**
** $Id: dld_tvobj.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#define Uses_TEvent
#include <string>
#include "dld_tvobj.h"
#include "dld_tvcontainer.h"
#include "dld_dialog.h"
#include "dld_tvapp.h"

DLD_TVObj::DLD_TVObj(const string& _name, DLD_TVDialog *pd) :
   hotk(0),
   dld_name(_name),
   width(0), height(0),
   dia(pd),
   isexit(false)
{
   set_dialog(pd);

   string::size_type i;
   i = dld_name.find("~");
   if (i != string::npos) {
      if(dld_name.compare("~", i+2))
	 hotk = 1;
   }

};

DLD_TVObj::~DLD_TVObj()
{
#ifdef DEBUG
   DLDdbg << "DLD_TVObj " << dld_name << " destruct!\n";
#endif
   dia = 0;
}

void DLD_TVObj::
activate ()
{
#ifdef DEBUG
   DLDdbg << "DLD_TVObj " << dld_name << " activate\n";
#endif

   DLD_Obj::activate ();

   if (dia && is_exit() && is_created)
   {
#ifdef DEBUG
      DLDdbg << dld_name << " called EXIT!!!\n";
      DLDdbg.flush ();
#endif
      // Generate Dialog exit event
      TEvent te;
      te.what = evCommand;
      te.message.command = cmOK;
      te.message.infoPtr = 0;
      dia->putEvent (te);
   }
}

string conname (const string& _str)
{
   string str = convstr (_str);
   string::size_type i;
   while ((i = str.find("ß")) != string::npos)
      str.replace(i, 1, "ss");

   while ((i = str.find("Ä")) != string::npos)
      str.replace(i, 1, "Ae");

   while ((i = str.find("Ö")) != string::npos)
     str.replace(i, 1, "Oe");

   while ((i = str.find("Ü")) != string::npos)
      str.replace(i, 1, "Ue");   

   while ((i = str.find("ä")) != string::npos)
      str.replace(i, 1, "ae");   

   if ((i = str.find("&")) != string::npos) {      
      str.replace(i, 2, string("~") + str.substr(i+1, 1) + string("~"));
   }

   while ((i = str.find("\t")) != string::npos) {
      str.replace(i, 1, " ");
      int lp = i - str.rfind("\n", i);
      for(int j = 7 - (lp%8); j > 0; j--) {
         str.insert(i, " ");
      }
   }

   return str;
}

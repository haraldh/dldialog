/******************************************************************************
**
** $Id: dld_dialog.cc,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_dialog.h"
#include "dld_gui.h"

extern char **environ;

DLD_Dialog::
DLD_Dialog(DLD_Gui *_parent, const DLD_Out& _out) : 
   out(_out),
   printvars(false),
   gui(_parent)
{
   set_dialog(this);
}

void DLD_Dialog::
set_env (const string& _name, const string& _value, DLD_Obj *_obj) 
{
   if(!_name.length()) {
      DLDerr << "set_env with empty _name called" << endl;
      return;
   }

#ifdef DEBUG 
   DLDdbg << "Setting " << _name << "=\"" << _value << "\"" 
	  << endl << flush;
#endif
   varmap[_name] = convstr(_value);
   varowner[_name] = _obj;
}

void DLD_Dialog::
del_env (const string& _name, DLD_Obj *_obj) 
{
   if(!_name.length()) {
      DLDerr << "del_env with empty _name called" << endl;
      return;
   }

   if((varowner[_name] == 0) || (varowner[_name] == _obj)) {
      DLDdbg << "Erasing " << _name  << endl << flush;
      /* Do not erase it, but set it to an empty string 
//      varmap.erase(varmap.find(_name));
//      varowner.erase(varowner.find(_name));
      */

      set_env(_name, "", _obj);
      varowner[_name] = 0;
   } 
}

bool DLD_Dialog::
test_env (const string& _name, const string& _value, bool substr) 
{
   VI i;

   // First lookup value in local varmap
   i = varmap.find(_name);

   if(i == varmap.end()) {
#ifdef DEBUG
      DLDdbg << _name << " not found in varmap!" << endl << flush;
#endif   
      return false;
   }

   if(substr) {
      string::size_type j;
      unsigned int vallen = _value.length();
      string &str = i->second;
      
#ifdef DEBUG
      DLDdbg << "Checking if \"" << str << "\" contains " << _value 
	     << endl << flush;
#endif   

      j = str.find(_value);
      
      if (j == string::npos)
	 return false;
      
      if ((j == 0) && (str.length() == vallen || str[j+vallen] == ' ')) {
#ifdef DEBUG
      DLDdbg << _value << " is the first in the string"
	     << endl << flush;
#endif   
	 return true;
      }
      
      if ((str[j-1] == ' ')) {
#ifdef DEBUG
      DLDdbg << _value << " is at position " << j
	     << endl << flush;
#endif   
	 if (str.length() == j+vallen) {
#ifdef DEBUG
	    DLDdbg << _value << " is the last in the string"
	      << endl << flush;
#endif   
	    return true;
	 }
	 
	 if ((str[j+vallen] == ' ') && (j+vallen <= str.length())) {
#ifdef DEBUG
	    DLDdbg << _value << " is in the middle of the string"
	      << endl << flush;
#endif   
	    return true;
	 }
      }		   
 
      return false;
   }
   else {
#ifdef DEBUG
      DLDdbg << "Checking if \"" << i->second << "\" == " << _value 
	     << endl << flush;
#endif   

      return (i->second.compare(_value) == 0);
   }
}

void DLD_Dialog::
set_up_environment()
{
   DLDdbg << "Setting up environment" << endl << flush;
   for(VI i = gui->envmap.begin(); i != gui->envmap.end(); ++i) {
      setenv(i->first.c_str(), i->second.c_str(), true);
      DLDdbg << i->first.c_str() << '=' << i->second.c_str() << endl << flush;
   }

   for(VI i = varmap.begin(); i != varmap.end(); ++i) {
      setenv(i->first.c_str(), i->second.c_str(), true);
      DLDdbg << i->first.c_str() << '=' << i->second.c_str() << endl << flush;
   }   
   DLDdbg << "Environment set up." << endl << flush;
}


string DLD_Dialog::
get_env (const string& _name) 
{
   return varmap[_name];
}

void DLD_Dialog::
register_var (const string& _name) 
{
   VI i;
   // First lookup value in local varmap
   i = varmap.find(_name);

   if(i == varmap.end()) {
      varmap[_name] = gui->get_env(_name);
   }
}

void DLD_Dialog::
register_gauge(DLD_Gauge *_gauge, int _fd) 
{
   gauges.push_back(_gauge);
   gui->register_gauge(_gauge, _fd);
}

void DLD_Dialog::
deregister_gauge(DLD_Gauge *_gauge, int _fd) 
{
   for(GI i = gauges.begin(); i != gauges.end(); ++i) {
      if (*i == _gauge) {
	 gauges.erase(i);
	 gui->deregister_gauge(*i);
	 break;
      }      
   }
}

DLD_Dialog::
~DLD_Dialog() 
{
   close();
}

void DLD_Dialog::
close() 
{
   for(GI i = gauges.begin(); i != gauges.end(); ++i) {
      gui->deregister_gauge(*i);
   }

   if(out.out && printvars) {
      for(VI i = varmap.begin(); i != varmap.end(); ++i) {
	 *(out.out) << i->first << "='" << i->second << "';" << endl;	 
      }
   }

   for(VI i = varmap.begin(); i != varmap.end(); i = varmap.begin())
      varmap.erase(i);

}

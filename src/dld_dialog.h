/******************************************************************************
**
** $Id: dld_dialog.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** by Harald Hoyer (dldialog@parzelle.de) 
** Copyright (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/


/******************************************************************************
 *
 * IMPORTANT:
 * ----------
 *
 * If you modify anything of this you have to modify 
 * GUI_VERSION_INFO in configure.in following the guidelines in
 * README.developers
 *
 *****************************************************************************/


#ifndef DLD_GUI_DIALOG_H
#define DLD_GUI_DIALOG_H

#include "dld_obj.h"
#include "dld_container.h"
#include "dld_out.h"

#include <sys/types.h>
#include <fstream.h>		// for ifstream
#include <unistd.h>
#include <string>
#include <map>
#include <list>

class DLD_Gui;
class DLD_Gauge;
typedef DLD_Gauge *DLD_Gauge_Ptr;
typedef list<DLD_Gauge_Ptr>::iterator GI;
typedef list<DLD_Gauge_Ptr> GaugeList;

/**
 * Abstract Interface
 * @short Abstract Interface
 * @author Harald Hoyer <dldialog@parzelle.de>
 */
class DLD_Dialog : public virtual DLD_Obj, public virtual DLD_Container {
public:
   DLD_Dialog(DLD_Gui *parent, const DLD_Out& out);
   virtual ~DLD_Dialog();

   virtual void close();

   /** Set a variable in this environment.
    * See man setenv(3)
    * @param _name the name of the variable
    * @param _value the value to set
    * @param _obj the object that sets the variable
    */
   void set_env (const string& _name, const string& _value, 
		 DLD_Obj *_obj);

   /** Delete a variable in this environment.
    * Deletes the variable if _obj was the one who set it.
    * @param _name the name of the variable
    * @param _obj the object that sets the variable
    */
   void del_env (const string& _name, DLD_Obj *_obj = 0);

   /** Get the value of a variable in this environment.
    * See man getenv(3)
    * @param name the name of the variable
    * @return a string to the value
    */
   string get_env (const string& _name);

   /**
    */
   void register_var (const string& _name);

   bool test_env(const string& _name, const string& _value, bool substr=false);

   void register_gauge(DLD_Gauge *_gauge, int _fd);
   void deregister_gauge(DLD_Gauge *_gauge, int _fd);

   const DLD_Out out;

   void set_up_environment();

protected:
   bool printvars;

private:
   map<const string, string> varmap;
   map<const string, DLD_Obj*> varowner;

   typedef map<const string, string>::iterator VI;

   GaugeList gauges;

   DLD_Gui *gui;
};

#endif

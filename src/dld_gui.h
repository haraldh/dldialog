/******************************************************************************
**
** $Id: dld_gui.h,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** by Harald Hoyer (Harald.Hoyer@hot.spotline.de) 
** for delix Computer GmbH (http://www.delix.de)
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


#ifndef DLD_GUI_H
#define DLD_GUI_H

#include "dld_out.h"
#include <string>
#include <map>

class DLD_Dialog;
class DLD_Gauge;

/**
 * Abstract Interface for all GUI modules.
 *
 * It provides virtual functions that have to be overwritten by 
 * the GUI modules.
 *
 * @short Abstract GUI Interface
 * @author Harald Hoyer <Harald.Hoyer@hot.spotline.de>
 */
class DLD_Gui 
{
public:
   /** Virtual Destruktor
    *
    */
   virtual ~DLD_Gui() {};

   /** Create the main dialog for this session
    * @param name The title of the dialog
    */
   virtual DLD_Dialog *dialog (const string& name, const DLD_Out& out) = 0;
   
   /** Show the dialog and communicate with the user.
    * If there is a message parsing loop it call DLD_Gui::parse()
    * if idle
    * @return 0 if all succeeds
    * @return >0 if an error occured
    */
   virtual int exec () = 0;

   /** Set the name of the GUI module
    * @param newname The name.
    * @return a reference to the name
    */
   virtual const string& name (const string& newname) = 0;

   /** Get the name of the GUI module
    * @return a reference to the name
    */
   virtual const string& name () = 0;

   /** Display a string
    * @param txt The text that is displayed to the user
    * @return 0 on success
    * @return >0 on error
    */
   virtual int print_status (const string& txt) = 0;

   /** Set a variable in this environment.
    * See man setenv(3)
    * @param _name the name of the variable
    * @param _value the value to set
    */
   void set_env (const string& _name, const string& _value);

   /** Get the value of a variable in this environment.
    * See man getenv(3)
    * @param name the name of the variable
    * @return a string to the value
    */
   string get_env (const string& _name);

   /** Remove all variables that are in this environment
    */
   void clear_env ();

   /** Must be called if the gui is idle.
    * @param microsec the time to wait in microseconds, 
    * if negative wait until input is ready
    */
   virtual bool parse(long wait);

   void register_gauge(DLD_Gauge *_gauge, int _fd);

   void deregister_gauge(DLD_Gauge *_gauge);

   map<const string, string> envmap;

private:
   typedef map<const string, string>::iterator VI;

   typedef DLD_Gauge *DLD_Gauge_Ptr;
   map<int, DLD_Gauge_Ptr> gaugemap;

};

#endif

/******************************************************************************
**
** $Id: dld_obj.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
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


#ifndef DLD_GUI_OBJ_H
#define DLD_GUI_OBJ_H

#include "dld_lib.h"

#include <sys/types.h>
#include <fstream.h>		// for ifstream
#include <unistd.h>
#include <string>
#include <list>

class DLD_Dialog;
class DLD_Container;

/**
 * Abstract interface for all GUI objects.
 *
 * Objects should not be used directly. Instead use the derived interface
 * classes returned by DLD_Container or other 'parent' objects.
 *
 * @short Abstract interface for all GUI objects.
 * @author Harald Hoyer <dldialog@parzelle.de>
 */
class DLD_Obj {
public:
   /** The default constructor.
    * Should be overloaded by the interface implementation.
    */
   DLD_Obj() : dialog(0), parent_obj(0), varaddflag(false), killchilds(true),
      execpid(0), is_disabled(false), is_movie(false), is_created(false) {};

   /** The default destructor.
    * Deletes all child objects and calls parent_obj->del_child(this)
    */
   virtual ~DLD_Obj();

   /** Sets the parent dialog for this object.
    * @param parent The parent dialog. Must not be NULL.
    */
   virtual void set_dialog(DLD_Dialog *parent) {
      Assert(Bad_arg, parent != 0);
      dialog = parent;
   };
   
   /** Adds an executable to the object.
    * This executable will be executed, if the object is activated.
    * Output will be parsed as a DLDialog program.
    * @param exec_string This string will be executed using "sh -c exec_string"
    * @return TRUE on success
    * @return ENOMEM if no memory for the exec_string could be allocated
    */
   virtual void add_exec (const string& exec_string) {
      execstr = convstr(exec_string);
   };

   /** 
    */
   virtual void set_killchild (bool flag) {
      killchilds = flag;
   }

   /** Adds an image to the object.
    * @param image_string The filename of the image.
    */
   virtual void add_image (const string& image_string) {
      imagestr = convstr(image_string);
      is_movie = false;
   };

   /** Adds an animated image to the object (gif, png, etc.).
    * @param image_string The filename of the image.
    */
   virtual void add_movie (const string& movie_string) {
      imagestr = convstr(movie_string);
      is_movie = true;
   };

   /** Set/Unset that the dialog should exit if this object is activated.
    * @param flag true or false.
    */
   virtual void set_exit(bool flag)  = 0;

   /** Set the width in percent.
    * @param _w the new width in percent of the parent width.
    */
   virtual void widthP (unsigned int _w) = 0;

   /** Set the height in percent.
    * @param _h the new height in percent of the parent height.
    */
   virtual void heightP(unsigned int _h) = 0;

   /** Activate this object.
    * Sets the assigned variable to varvalue.
    * Executes a program specified with add_exec.
    * Exits the dialog if set_exit(true) was set.
    */
   virtual void activate();

   /** Deactivates the object.
    * The function sets assigned variable to the old value. 
    */
   virtual void deactivate();

   /** Binds an environment variable to the object.
    * This variable will be set to the value specified, if the object
    * is activated.
    * @param name the name of the variable
    * @param val the value to set
    */
   void add_setvar (const string& name, const string val);

   /** Binds an environment variable to the object.
    * This variable will be set to the value specified, if the object
    * is activated.
    * @param name the name of the variable
    * @param val the value to add
    * @return TRUE if all succeeded
    */
   void add_addvar (const string& name, const string val);


   void set_font (const string &, const string &);

   void set_bg (const string &bg );

   void set_fg (const string &fg );

   /** Compare the assigned variable with a value.
    * @param _value The value.
    */
   virtual bool test_env (const string& _value);

   /** Compare the assigned variable with varvalue.
    */
   virtual bool test_env ();

   /** Create the Object.
    * This function should be overloaded with the interface implementation.
    * It indicates that the object has all of it's parameters set and can
    * be created and shown.
    */
   virtual void create();

   /** Add a child object to the child list.
    * The child object will be deleted before this object is deleted.
    * The variable parent_obj of the child is set to this object.
    * @param child The child object.
    */
   virtual void add_child(DLD_Obj *child);

   /** Deletes a child object form the child list.
    * The child object will only removed from the child list.
    * child->parent_obj will not be touched 
    * nor will it delete the child itsself. 
    * @param child The child object.
    */
   virtual void del_child(DLD_Obj *child);

   /** Disables the object
    */
   virtual void disable() { is_disabled = true;};

   /** Indicates that the object was created and is visible
    */
   virtual bool was_created() { return is_created; };

   
protected:
   typedef DLD_Obj *DLD_Obj_Ptr;
   /** The child list.
    */
   list<DLD_Obj_Ptr>  childlist;
   typedef list<DLD_Obj_Ptr>::iterator CI;

   /** The parent dialog the object is in.
    */
   DLD_Dialog *dialog;

   /** The parent object, this object is tied to.
    */
   DLD_Obj *parent_obj;

   /** The name of the assigned variable.
    */
   string varname;

   /** A string that an assigned variable will be set to, if this object 
    * is activated.
    */
   string varvalue;

   /** This variable holds the old value of the assigned variable to do an
    * deactivate.
    */
   string oldvalue;

   /** If this bool variable is set true, varvalue will be concatenated to
    * the assigned variables value.
    */
   bool varaddflag;

   /** A string that will be executed using:
    * /bin/sh -c "execstr"
    */
   string execstr;

   /** Flag indicating whether to kill the childs upon exiting r not
    * true: kill
    * false: do not kill it
    */
   bool killchilds;

   /** The pid of the executed command
    */
   pid_t execpid;

   /** An image that will be displayed (currently only in a qt button) 
    */
   string imagestr;

   /** A fontname for the text in qt list
    */
   string fontname;

   /** A backgroungcolor for the text (doesn't work now)
    */
   string bg_color;

   /** A foregroungcolor for the text 
    *  (at the moment only in button and listitem)
    */
   string fg_color;

   /** The fontsize
    */
   int fontsize;

   /** Indicates if the object is disabled.
    */
   bool is_disabled;

   /** Indicates that the imagestr contains an animated image
    */
   bool is_movie;

   /** Indicates that the object was created and is visible
    */
   bool is_created;

};
#endif

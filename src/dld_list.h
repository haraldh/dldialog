/******************************************************************************
**
** $Id: dld_list.h,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
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


#ifndef DLD_GUI_LIST_H
#define DLD_GUI_LIST_H

#include "dld_obj.h"

class DLD_ListItem;

/**
 * The list.
 * A list consists of several listitems. These are displayed one per line.
 * The user can select one of them or several if set_multi(true) was called.
 *
 * At creation time all listitem that have their variables set should be 
 * activated. After that the variable of the list itsself takes effect.
 * 
 * The listitems and the list itsself should be 'activate'd and 'deactivate'd
 * every time the selection changes.
 *
 * @short Abstract interface for the list object.
 * @author Harald Hoyer <Harald.Hoyer@hot.spotline.de>
 */
class DLD_List : public virtual DLD_Obj {
public:
   /** Adds a listitem to the list.
    * @param name The text of the listitem
    * @return ptr to DLD_ListItem
    */
   virtual DLD_ListItem * listitem (const string&  = 0) = 0;

   virtual void set_multi(bool on) { is_multi = on; };

   /** Indicates the beginning of a new block
    *
    * Can be used to reserve space for children.
    */
   virtual void open_brace() = 0;

   /** Indicates the end of a block.
    *
    * Can be used to collect all children.
    */
   virtual void close_brace() = 0;

   /** Compare the assigned variable with a value.
    * @param _value The value.
    */
   virtual bool test_env (const string& _value) {
      bool ret;
      if(is_multi)
	 varaddflag = true;
#ifdef DEBUG
   DLDdbg << "checking " << _value << " varaddflag = " << varaddflag << endl << flush;
#endif   
      ret = DLD_Obj::test_env(_value);
      varaddflag = false;
      return ret;
   };

protected:
   /** Indicates that the list is a multiselection list
    */
   bool is_multi;
};

#endif

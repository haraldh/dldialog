/******************************************************************************
**
** $Id: dld_checklist.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
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


#ifndef DLD_GUI_CHECKLIST_H
#define DLD_GUI_CHECKLIST_H

#include "dld_obj.h"

class DLD_CheckButton;

/**
 * The checklist.
 *
 * A checklist consists of several checkbuttons.
 * The user can select several of them.
 *
 * At creation time all checkbuttons that have their variables set should be 
 * activated. After that the variable of the checklist itsself takes effect,
 * but no deactivation should be performed.
 * 
 * The checkbuttons and the checklist itsself should be 'activate'd 
 * and 'deactivate'd every time the selection changes.
 *
 * @short Abstract Interface
 * @author Harald Hoyer <dldialog@parzelle.de>
 */
class DLD_CheckList : public virtual DLD_Obj {
public:
   /** Adds a checkbutton to the checklist.
    * @param name The text of the item
    * @return ptr to item
    */
   virtual DLD_CheckButton *checkbutton(const string&  = 0) = 0;

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
      varaddflag = true;
      ret = DLD_Obj::test_env(_value);
      varaddflag = false;
      return ret;
   };
};
#endif

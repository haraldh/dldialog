/******************************************************************************
**
** $Id: dld_combobox.h,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
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


#ifndef DLD_GUI_COMBOBOX_H
#define DLD_GUI_COMBOBOX_H

#include "dld_obj.h"

class DLD_ComboItem;

/**
 * Abstract Interface
 * @short Abstract Interface
 * @author Harald Hoyer <Harald.Hoyer@hot.spotline.de>
 */
class DLD_ComboBox : public virtual DLD_Obj {
public:
   /** Adds a comboitem to the combobox.
    * @param name The text of the item
    * @return ptr to item
    */
   virtual DLD_ComboItem *comboitem(const string&  = 0) = 0;

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
};
#endif
/******************************************************************************
**
** $Id: dld_input.h,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
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


#ifndef DLD_GUI_INPUT_H
#define DLD_GUI_INPUT_H

#include "dld_obj.h"

/**
 * Abstract Interface
 * @short Abstract Interface
 * @author Harald Hoyer <Harald.Hoyer@hot.spotline.de>
 */
class DLD_Input : public virtual DLD_Obj {
public:
   /** Make the input to accept only IP nummers
    * @param flag true or false
    */
   virtual void set_ip(bool flag) = 0;

   /** Make the input invisible
    * @param flag true or false
    */
   virtual void set_passwd(bool flag) = 0;

   /** Set the maximal length of the input field
    * @param len the length
    */
   virtual void set_length(int len) = 0;

   /** Make the input to accept only numeric input
    * @param flag true or false
    */
   virtual void set_numeric(bool flag) = 0;
};
#endif

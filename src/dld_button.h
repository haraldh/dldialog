/******************************************************************************
**
** $Id: dld_button.h,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
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


#ifndef DLD_GUI_BUTTON_H
#define DLD_GUI_BUTTON_H

#include "dld_obj.h"

/**
 * Abstract Interface
 * @short Abstract Interface
 * @author Harald Hoyer <Harald.Hoyer@hot.spotline.de>
 */
class DLD_Button : public virtual DLD_Obj {
public:
   virtual void set_signature(bool on) {
      signature = on;
   };

protected:
   bool signature;
};
#endif
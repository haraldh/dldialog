/******************************************************************************
**
** $Id: dld_checkbutton.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
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


#ifndef DLD_GUI_CHECKBUTTON_H
#define DLD_GUI_CHECKBUTTON_H

#include "dld_obj.h"

/**
 * The checkbutton.
 * checkbuttons should be created using DLD_CheckList->checkbutton().
 *
 * @short Abstract interface for the checkbutton.
 * @author Harald Hoyer <dldialog@parzelle.de>
 */
class DLD_CheckButton : public virtual DLD_Obj {
};
#endif

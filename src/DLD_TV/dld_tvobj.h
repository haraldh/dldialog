/******************************************************************************
**
** $Id: dld_tvobj.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_TVOBJ_H
#define DLD_TVOBJ_H

#include "../dld_obj.h"
#include "dld_geom.h"
#include "dld_tvlib.h"
#define Uses_TView
#define Uses_TRect
#define Uses_TSItem
#include <tvision/tv.h>

class DLD_TVDialog;
class DLD_TVContainer;

/** Common class for all TVision objects.
 *
 * @short Common class for all TVision objects.
 * @author Harald Hoyer <dldialog@parzelle.de>
 * 
 */
class DLD_TVObj : public virtual DLD_Obj
{
public:
   /// Constructor
   DLD_TVObj(const string& name, DLD_TVDialog *pd);

   /// Destructor
   virtual ~DLD_TVObj();

   /** Set/Unset that the dialog should exit if item is activated.
    * @param flag Bool
    */
   virtual void set_exit(bool flag) {isexit = flag;};

   /** Set the width in percent.
    * @param _w the new width
    */
   virtual void    widthP (unsigned int _w) { lenWidth.setPer(_w); };

   /** Set the height in percent.
    * @param _h the new height
    */
   virtual void    heightP(unsigned int _h) { lenHeight.setPer(_h); };
   
   virtual void create() = 0;

   bool hotk;

   virtual void changeBounds( const TRect& bounds ) = 0;

   Len lenWidth;
   Len lenHeight;

   string dld_name;

   virtual void setGeom(const TRect& _g) { geom = _g; };
   
   virtual void calcBounds(TRect& bounds, TPoint delta ) = 0;

   virtual void activate();

   virtual bool is_exit() {return isexit;};

protected:

   unsigned int width, height;

   TRect geom;

   DLD_TVDialog *dia;

private: 
   bool isexit;
};

#endif

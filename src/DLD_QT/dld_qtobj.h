/******************************************************************************
**
** $Id: dld_qtobj.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_QTOBJ_H
#define DLD_QTOBJ_H

#include "../dld_obj.h"
#include <qwidget.h>

class DLD_QTContainer;
class DLD_QTDialog;
class DLD_QTApp;

/** Basic class for DLD_QT objects providing common methods.
 *
 */
class DLD_QTObj : public virtual DLD_Obj
{
public:
   /// Constructor
   DLD_QTObj(const string& name, DLD_QTDialog *pd);

   /// Destructor
   virtual ~DLD_QTObj();

   /** Set/Unset that the dialog should exit if item is activated.
    * @param flag Bool
    */
   virtual void set_exit(bool flag) { isexit = flag;};

   /** Set the width in percent.
    * @param _w the new width in percent of the parent width
    */
   virtual void widthP (unsigned int _w) {obj_widthP = _w;};

   /** Set the height in percent.
    * @param _h the new height in percent of the parent height
    */
   virtual void heightP(unsigned int _h) {obj_heightP = _h;};

   virtual void create() = 0;

   virtual void activate();

   virtual bool is_exit() {return isexit;};   

   /// name 
   string dld_name;

   int obj_widthP, obj_heightP;

   bool fixed_width, fixed_height;

protected:
   ///
   DLD_QTDialog *pardia;

   ///
   DLD_QTApp *app;

private: 
   bool isexit;
};

#endif

/******************************************************************************
**
** $Id: dld_gauge.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
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


#ifndef DLD_GUI_GAUGE_H
#define DLD_GUI_GAUGE_H

#include "dld_obj.h"
#include "dld_dialog.h"

/** An assertion function for use with dldialog.
 * @short An assertion function for use with dldialog
 * @author Harald Hoyer <dldialog@parzelle.de>
 */
class DLD_Gauge : public virtual DLD_Obj {
public:
   DLD_Gauge() : execpid(0), gaugefd(0) {};
   virtual ~DLD_Gauge();
   /** Update the progress meter.
    * @param _p the new percentage from 0..100
    */
   virtual void set_progress(int _p) = 0;

   /** Executes the specified executable.
    *
    */
   virtual void create();

   virtual void add_exec (const string& exec_string) {
      gaugestr = convstr(exec_string);
   };

   virtual void parse();

   pid_t execpid;
   
private:
   string gaugestr;
   int gaugefd;
   ifstream in;
};
#endif

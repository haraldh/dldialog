/******************************************************************************
**
** $Id: dld_qtapp.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_QTAPP_H
#define DLD_QTAPP_H

#include "../dld_gui.h"
#include "dld_qtlib.h"
#include "dld_qtobj.h"
#include "dld_dialog.h"
#include <qapp.h>

/** The main interface class for the qt module.
 *
 */
class DLD_QTApp :  public QApplication, public DLD_Gui
{
   ///
   Q_OBJECT;
public:
   /// Constructor
   DLD_QTApp (const string& _name, int argc, char **argv);

   /// Destructor
   virtual ~DLD_QTApp ();
   
   DLD_Dialog *dialog (const string& _name , const DLD_Out& out);
   
   /// Virtual function.
   int exec();

   const string& name(const string& newname);

   /// Virtual function.
   const string& name () {
      return guiname;
   };

   /// Virtual function.
   int print_status (const string& text);

   void del_child(DLD_QTDialog *dia);

   int add_child (DLD_QTDialog *dia);

   ///
   DLD_QTDialog *mainDialog;

///
public slots:
//   void  slot_has_exited(DLD_QTDialog *);
   void  slot_has_exited(void);

protected:

   typedef DLD_QTDialog *DLD_QTDialog_Ptr;
   list<DLD_QTDialog_Ptr>  childlist;
   bool childlock;
   typedef list<DLD_QTDialog_Ptr>::iterator CI; 

   bool app_done;

private:
///
   string guiname;
   bool running;
   ///
   QRect init_size;
   
};

#endif

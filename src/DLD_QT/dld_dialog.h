/******************************************************************************
**
** $Id: dld_dialog.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_QTDIALOG_H
#define DLD_QTDIALOG_H

#include "../dld_dialog.h"
#include "dld_qtcontainer.h"
#include <qdialog.h>
#include <qgrpbox.h>
#include <qlayout.h>
#include <qmenubar.h>

/** provides an user dialog in qt style for dldialog.
 *
 */
class DLD_QTDialog: public QDialog, public DLD_QTContainer, public DLD_Dialog
{
   Q_OBJECT;

public:

   ///
   DLD_QTDialog(const string& name, DLD_QTApp *aptr, const DLD_Out path);
   ///
   virtual ~DLD_QTDialog();

   ///
   void create();

   ///
   virtual void done(int);

   ///
   void cleanup() ;

   void close_brace() { create(); };

   ///
   QRect init_size;

   int set_name (const string& name);

   void insert (QWidget * w, DLD_QTObj *obj);

   bool isEmpty() {
      return empty;
   }

   void setGeometry ( int x, int y, int w, int h );

signals:
   ///
   void has_exited();

protected:
   ///
//   QGridLayout *toplayout;
   QVBoxLayout *toplayout;
   ///
   QMenuBar *menu;  
   
   int dld_rows;
   bool empty, first_time;
   map<int, DLD_QTObj*> qtobjs;
   map<int, QWidget*> qtwidgets;

protected slots:
   virtual void closeEvent ( QCloseEvent * );
};

#endif

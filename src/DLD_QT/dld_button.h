/******************************************************************************
**
** $Id: dld_button.h,v 1.1 2001/03/14 02:33:07 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de>
**
******************************************************************************/

#ifndef DLD_QTBUTTON_H
#define DLD_QTBUTTON_H

#include "../dld_button.h"
#include "dld_qtobj.h"
#include <qwidget.h>
#include <qpushbt.h>
#include <qpixmap.h>
#include <qmovie.h>

/** The button class in qt style.
 *
 */
class DLD_QTButton :  public QPushButton, public DLD_QTObj, public DLD_Button
{
   Q_OBJECT;
public:
   ///
   DLD_QTButton(QWidget *_parent, const string& name, DLD_QTDialog *pd);
   ///
   virtual ~DLD_QTButton();
   ///
   void create();

   /** Disables the object
    */
   virtual void disable() {
      setEnabled(FALSE);
   };

///
public slots:
   int slot_activate();
   void movieStatus(int);   
   void movieUpdate(const QRect&);   
   void movieResized(const QSize&);
  
protected:
   void drawButtonLabel ( QPainter * paint );
   void drawButtonPixmap ( QPainter * paint,  const QRect& area );
   bool bigpic;
   void getPixmap();
   QMovie movie;
   QPixmap pix;
};

#endif

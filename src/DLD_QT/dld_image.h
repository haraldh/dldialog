/******************************************************************************
**
** $Id: dld_image.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_QTIMAGE_H
#define DLD_QTIMAGE_H

#include "../dld_image.h"
#include "dld_qtobj.h"
#include <qwidget.h>
#include <qpixmap.h>
#include <qmovie.h>

/** The image class in qt style.
 *
 */
class DLD_QTImage :  public QWidget, public DLD_QTObj, public DLD_Image
{
   Q_OBJECT;
public:
   ///
   DLD_QTImage(QWidget *_parent, const string& name, DLD_QTDialog *pd);
   ///
   virtual ~DLD_QTImage();
   ///
   void create();
   void paintEvent(QPaintEvent*);

 public slots:
   void movieStatus(int);   
   void movieUpdate(const QRect&);   
   void movieResized(const QSize&);

protected:
   void getPixmap();

private:
   QMovie movie;
   QPixmap pix;
};

#endif

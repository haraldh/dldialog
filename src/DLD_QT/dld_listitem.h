/******************************************************************************
**
** $Id: dld_listitem.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_QTLISTITEM_H
#define DLD_QTLISTITEM_H

#include "../dld_listitem.h"
#include "dld_qtobj.h"
#include <qlistbox.h>
#include <qpixmap.h>


class DLD_QTDialog;
class QWidget;

/** The listitem in qt style for use with @ref DLD_List.
 *
 */
class DLD_QTListItem : public QListBoxText, public DLD_QTObj, 
		       public DLD_ListItem
{
public:
   ///
   DLD_QTListItem(QWidget *_parent, const string& name, DLD_QTDialog *pd);

   ///
   virtual ~DLD_QTListItem();

   ///
   void create();

protected:
   virtual void paint( QPainter * );
   virtual int height( const QListBox * ) const;
   virtual int width( const QListBox * ) const;
   virtual const QPixmap *pixmap() { return &pm; }

private:
   QPixmap pm;

};

#endif

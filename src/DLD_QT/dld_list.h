/******************************************************************************
**
** $Id: dld_list.h,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
******************************************************************************/
#ifndef DLD_QTLIST_H
#define DLD_QTLIST_H

#include "../dld_list.h"
#include "dld_qtobj.h"
#include <qlistbox.h> 
#include <qptrdict.h>

class DLD_QTListItem;
class DLD_ListItem;

/**  The list class in qt style.
 */

class DLD_QTList : public QListBox, public DLD_QTObj, public DLD_List
{
   Q_OBJECT;
public:
   ///
   DLD_QTList(QWidget *_parent, const string& name, DLD_QTDialog *pd);

   ///
   virtual ~DLD_QTList();

   ///
   QSize sizeHint();

   void DLD_QTList::set_font(char*, int);

   /** Adds a listitem to the list.
    * @param name The text of the listitem
    * @return ptr to DLD_ListItem
    */
   DLD_ListItem * listitem (const string&);

   ///
   void create();

   void set_multi(bool);

   /** Indicates the beginning of a new block
    *
    * Can be used to reserve space for children.
    */
   void open_brace() {};

   /** Indicates the end of a block.
    *
    * Can be used to collect all children.
    */
   void close_brace() {};

public slots:
   void slotSelected(int index);

protected:
   ///
   QPtrDict<DLD_QTListItem> dict;
};

#endif

/******************************************************************************
**
** $Id: dld_radiolist.h,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#ifndef DLD_QTRADIOLIST_H
#define DLD_QTRADIOLIST_H

#include "../dld_radiolist.h"
#include "dld_qtlib.h"
#include "dld_qtobj.h"
#include "dld_radio.h"
#include <qbttngrp.h> 
#include <qlayout.h>

/** A class providing container methods for @ref DLD_Radio.
 *
 */
class DLD_QTRadioList : public QButtonGroup,
			public DLD_QTObj, public DLD_RadioList
{
   Q_OBJECT;

public:
   ///
   DLD_QTRadioList(QWidget *_parent, const string& name, DLD_QTDialog *pd);

   ///
   virtual ~DLD_QTRadioList();

   /** Adds a radiobutton to the radiolist.
    * @param name The text of the item
    * @return ptr to item
    */
   DLD_RadioButton *radiobutton(const string&);

   ///
   void create();

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
   void slot_rbpress (int num);


private:
   ///
   int count;
   QVBoxLayout *topLayout; 

   typedef DLD_QTRadioButton *DLD_QTRadioButton_Ptr;
   /** The child list.
    */
   list<DLD_QTRadioButton_Ptr>  rb_childlist;
   typedef list<DLD_QTRadioButton_Ptr>::iterator RBI;

};

#endif

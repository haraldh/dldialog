/******************************************************************************
**
** $Id: dld_text.h,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
**
******************************************************************************/

#ifndef DLD_TEXT_H
#define DLD_TEXT_H

#include "../dld_text.h"
#include "dld_qtobj.h"
#include <qlabel.h>

/** Displays a text line in the dialog.
 *
 */
class DLD_QTText : public QLabel, public DLD_QTObj, public DLD_Text
{
public:
   ///
   DLD_QTText(QWidget *_parent, const string& name, DLD_QTDialog *pd);

   ///
   virtual ~DLD_QTText();

   ///
   void create();  

   void drawContents(QPainter *);

};

#endif

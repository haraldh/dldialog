/************************************************************************
**
** $Id: dld_textbox.h,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
************************************************************************/

#ifndef DLD_QTTEXTBOX_H
#define DLD_QTTEXTBOX_H

#include "../dld_textbox.h"
#include "dld_qtobj.h"
#include <qmultilinedit.h>

/** Displays a text file in the dialog.
 *
 */
class DLD_QTTextBox : public QMultiLineEdit, public DLD_TextBox, 
		      public DLD_QTObj
{
public:
   ///
   DLD_QTTextBox(QWidget *_parent, const string& name, DLD_QTDialog *pd);
   ///
   ~DLD_QTTextBox();
  ///
   void create();

   /** Sets the filename of the file that will be printed
    * @param fname the filename
    */
   void set_filename(const string& fname);

   ///
   void text_parse(const char *p);

   ///
   QSize sizeHint ();

private:
   int nlines;
   string filename;
};

#endif

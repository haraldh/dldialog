/******************************************************************************
**
** $Id: dld_textbox.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_textbox.h"
#include <qfile.h>
#include <qtextstream.h>
#include <iostream.h>

DLD_QTTextBox::
DLD_QTTextBox (QWidget *_parent, const string& name, DLD_QTDialog *pd):
   QMultiLineEdit (_parent),
   DLD_QTObj (name, pd)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "textbox " << dld_name 
	  << " constructed " << endl
	  << flush;
#endif

   nlines = 0;
}


QSize DLD_QTTextBox::
sizeHint ()
{
   return QSize (QMultiLineEdit::sizeHint().width() + 10,
		 10 + fontMetrics ().height () * nlines);
}

DLD_QTTextBox::
~DLD_QTTextBox ()
{
}

void DLD_QTTextBox::
set_filename(const string& fname)
{
   filename = fname;
}

void DLD_QTTextBox::
create ()
{
   setReadOnly(TRUE);
   setAutoUpdate( FALSE );
   clear();

   if ( fontname.length() > 0 ) {
      QFont newfont( fontname.c_str() , fontsize, false );
      this->setFont( newfont );
   }

   if(filename.length())
   {
      QFile f( filename.c_str() );
      if ( f.open( IO_ReadOnly ) )
      {      
	 QTextStream t(&f); 
	 
	 while ( !t.eof() ) {
	    QString s = t.readLine();
	    append( s );
	    nlines++;
	 }    
	 
	 f.close();
      }
   }
   else
      setText(dld_name.c_str());
   
   setAutoUpdate( TRUE );
   repaint();
   
   setMinimumWidth (fontMetrics ().maxWidth () * 10 + 10);
   setMinimumHeight (fontMetrics ().height () * 3 + 10);
   DLD_Obj::create();
}

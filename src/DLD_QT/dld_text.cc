/******************************************************************************
**
** $Id: dld_text.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
**
******************************************************************************/

#include "dld_qtlib.h"
#include "dld_text.h"
#include <qpainter.h> 

#include <iostream.h>

DLD_QTText::
DLD_QTText (QWidget *_parent, const string& name, DLD_QTDialog *pd) :
   QLabel (convstr(name).c_str(), _parent),
   DLD_QTObj (name, pd)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "text " << dld_name 
	  << " constructed " << endl
	  << flush;
#endif
   fixed_height = fixed_width = true;
}

DLD_QTText::
~DLD_QTText ()
{
}

void DLD_QTText::
create ()
{
  if ( fontname.length() > 0 ) {
     QFont newfont( fontname.c_str() , fontsize, false );
     this->setFont( newfont );
  }

  if (bg_color.length() > 0)
     setBackgroundColor(QColor(bg_color.c_str()));

  repaint();
  setFixedWidth (sizeHint ().width ());
  setFixedHeight (sizeHint ().height ());
  DLD_Obj::create();
}

void DLD_QTText::drawContents( QPainter *p )
{  
   if (fg_color.length() > 0)
      p->setPen(QColor(fg_color.c_str()));

   QLabel::drawContents(p);
}

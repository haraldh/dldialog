/******************************************************************************
**
** $Id: dld_listitem.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
******************************************************************************/
#include "dld_qtlib.h"
#include "dld_listitem.h"
#include <qpixmap.h>
#include <qpainter.h> 
#include <qwidget.h> 

#include <iostream.h>

DLD_QTListItem:: 
DLD_QTListItem (QWidget *, const string& name, DLD_QTDialog *pd):
   QListBoxText (), 
   DLD_QTObj (name, pd)
{
   QListBoxText::setText(dld_name.c_str());
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "listitem ";
#endif
}

DLD_QTListItem::
~DLD_QTListItem ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "listitem deleted\n";
#endif
}

void DLD_QTListItem::create () {
   if (imagestr.length() > 0 ) 
   {
      pm.load(imagestr.c_str());
      if(pm.isNull()) {
	 DLDerr << "image " << imagestr << _(" could not be loaded")
		<< endl << flush;
      }
   }
   DLD_Obj::create();

}

void DLD_QTListItem::paint( QPainter *p )
{  
   // store the old settings
   QPen oldpen(p->pen());
   QColor oldbg(p->backgroundColor ());
   QFont oldfont(p->font());
   if ( fontname.length() > 0 )
      p->setFont( QFont( fontname.c_str() , fontsize, false ));
   
   if (fg_color.length() > 0)
      p->setPen(QColor(fg_color.c_str()));

   if (bg_color.length() > 0)
      p->setBackgroundColor(QColor(bg_color.c_str()));

   if(!pm.isNull()) {
      p->drawPixmap( 0, 0, pm );
   }

   QFontMetrics fm = p->fontMetrics();
   int yPos;                       // vertical text position
   if ( pm.height() < fm.height() )
      yPos = fm.ascent() + fm.leading()/2;
   else
      yPos = pm.height()/2 - fm.height()/2 + fm.ascent();
   p->drawText( pm.width() + 5, yPos, text() );

   // restore the old settings
   p->setFont( oldfont );
   p->setPen(oldpen);
   p->setBackgroundColor(oldbg);
}

int DLD_QTListItem::height(const QListBox *lb ) const
{
   return QMAX( pm.height() + 1, lb->fontMetrics().lineSpacing() + 1 );
}

int DLD_QTListItem::width(const QListBox *lb ) const
{
   return pm.width() + lb->fontMetrics().width( text() ) + 6;
}


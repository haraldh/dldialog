/******************************************************************************
**
** $Id: dld_button.cc,v 1.1 2001/03/14 02:33:07 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
!******************************************************************************/
#include "dld_qtlib.h"
#include "dld_button.h"
#include "dld_dialog.h"
#include <iostream.h>
#include <qpainter.h>
#include <qbitmap.h>

DLD_QTButton::DLD_QTButton (QWidget *_parent, 
			    const string& name, DLD_QTDialog *pd):
   QPushButton (convstr(name).c_str(), _parent),
   DLD_QTObj (name, pd),
   bigpic(false)
{
   signature = false;
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "button " << dld_name 
	  << " constructed " << endl
	  << flush;
#endif
   if ( fontname.length() > 0 )
     this->setFont( QFont( fontname.c_str() , fontsize, false ) );
   

   setMinimumWidth (sizeHint ().width ());
   setFixedHeight (sizeHint ().height ());
   fixed_height = true;

   connect (this, SIGNAL (clicked ()), SLOT (slot_activate ()));
}

DLD_QTButton::
~DLD_QTButton ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "button deleted\n";
#endif
}

void DLD_QTButton::movieStatus( int status)
{
   if (status < 0) {
#ifdef DEBUG
      DLDdbg << DLD_LIB_PREFIX "button is no movie status = " << status << endl << flush;
#endif
      movie.disconnectStatus(this, SLOT(movieStatus(int)));
      movie.disconnectUpdate(this, SLOT(movieUpdate(const QRect&)));
      movie.disconnectResize(this, SLOT(movieResized(const QSize&)));      
      getPixmap();
   }
   else {
      is_movie = true;
      movie.setBackgroundColor(backgroundColor());

#ifdef DEBUG
      DLDdbg << DLD_LIB_PREFIX "button is movie!!" << endl << flush;
#endif
   }
}

void DLD_QTButton::movieUpdate( const QRect& area)
{
   QPainter paint( this );   

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "button update." << endl << flush;
#endif      
   if(movie.frameNumber() == 1) {
      const QBitmap& bmap = QBitmap();
      QPixmap& pmap = const_cast<QPixmap&>(movie.framePixmap());
      pmap.setMask(bmap);
   }
   drawButtonPixmap(&paint, area);
}

void DLD_QTButton::movieResized(const QSize& size)
{
   QSize pushs = QPushButton::minimumSize();
   if(signature) {
      setMinimumSize(QSize(max(pushs.width(), size.width()+8),
			   pushs.height() + size.height() ));
      setFixedHeight (pushs.height() + size.height());
      //setIsMenuButton(TRUE);
      bigpic = true;
   }
   else {
      setMinimumSize(QSize(pushs.width() + size.width() - 10,
			   max(pushs.height(), size.height()+4)));
      setFixedHeight (max(pushs.height(), size.height()+4));
   }
//   resize( minimumSize().width() , minimumSize().height() );
   repaint();
}

void DLD_QTButton::getPixmap()
{
   pix.load(imagestr.c_str());
   if(pix.isNull()) {
      DLDerr << "image " << imagestr << _(" could not be loaded")
	     << endl << flush;
   }
   else {
      QSize pushs = QPushButton::minimumSize(), pixs = pix.size();
      if(signature) {
	 setMinimumSize(QSize(max(pushs.width(), pixs.width()+8),
			      pushs.height() + pixs.height() ));
	 setFixedHeight (pushs.height() + pixs.height());
	 //setIsMenuButton(TRUE);
	 bigpic = true;
      }
      else {
	 setMinimumSize(QSize(pushs.width() + pixs.width() - 10,
			      max(pushs.height(), pixs.height()+4)));
	 setFixedHeight (max(pushs.height(), pixs.height()+4));
      }
   }
   repaint();
}

void DLD_QTButton::
create ()
{
   if(imagestr.length()) {
      if(is_movie) {
	 movie = QMovie(imagestr.c_str());
	 
	 if(movie.isNull()) {
#ifdef DEBUG
	    DLDdbg << DLD_LIB_PREFIX "button is no movie" << endl << flush;
#endif
	    getPixmap();
	 }
	 else {
	    movie.connectStatus(this, SLOT(movieStatus(int)));
	    movie.connectUpdate(this, SLOT(movieUpdate(const QRect&)));
	    movie.connectResize(this, SLOT(movieResized(const QSize&)));      
	 }
      }
      else {
	 getPixmap();
      }
   }       
   DLD_Obj::create();
}

int DLD_QTButton::
slot_activate ()
{
   DLD_QTObj::activate ();
   return 0;
}


void DLD_QTButton::drawButtonLabel ( QPainter * p )
{
   bool pressed = false;
   QPixmap pm;

   if ( fontname.length() > 0 )
     p->setFont( QFont( fontname.c_str() , fontsize, false ) );
   if (bg_color.length() > 0)
     p->setBackgroundColor(QColor(bg_color.c_str()));

   if(is_movie) {
#ifdef DEBUG
	 DLDdbg << DLD_LIB_PREFIX "movie pixmap" << endl << flush;
#endif
      pm = movie.framePixmap();
   }
   else {
#ifdef DEBUG
	 DLDdbg << DLD_LIB_PREFIX "normal pixmap" << endl << flush;
#endif
      pm = pix;
   }

   if(!pm.isNull()) {            
      QRect r = rect();
      int x, y, w, h;
      r.rect( &x, &y, &w, &h );
      if ( (isDown() || isOn()) && style() == WindowsStyle ) {
	 // shift pixmap/text
	 x++;
	 y++;
	 pressed = true;
      }

      if(!bigpic) {      
	 x += pm.width()+12;  y += 2;  w -= 14+pm.width();  h -= 4;
	 
	 const QColorGroup g(colorGroup());
	 if (fg_color.length() > 0)
	   p->setPen(QColor(fg_color.c_str()));
	 else
	   p->setPen( g.text() );
	 
	 if ( style() == WindowsStyle && !isEnabled() ) {
	    p->setPen( g.light() );
	    p->drawText( x+1, y+1, w, h, AlignCenter|ShowPrefix, text(), -1 );
	    p->setPen( g.text() );
	 }
	 
	 p->drawText( x, y, w, h, AlignCenter|ShowPrefix, text(), -1 );
      }
      else {
	 x += 2;  y += pm.height()+7;  w -= 4;  h -= pm.height()+9;
	 
	 const QColorGroup g(colorGroup());
	 if (fg_color.length() > 0)
	   p->setPen(QColor(fg_color.c_str()));
	 else
	   p->setPen( g.text() );
	 
	 if ( style() == WindowsStyle && !isEnabled() ) {
	    p->setPen( g.light() );
	    p->drawText( x+1, y+1, w, h, AlignCenter|ShowPrefix, text(), -1 );
	    p->setPen( g.text() );
	 }
	 if (fg_color.length() > 0)
	   p->setPen(QColor(fg_color.c_str()));	 
	 p->drawText( x, y, w, h, AlignCenter|ShowPrefix, text(), -1 );
      }
      drawButtonPixmap(p, QRect());
   }
   else {
#ifdef DEBUG
	 DLDdbg << "pixmap was null" << endl << flush;
#endif
      QPushButton::drawButtonLabel(p);
   }
}

void DLD_QTButton::drawButtonPixmap ( QPainter * p ,  const QRect& area)
{
   bool pressed = false;
   QPixmap pm;
   
   if(is_movie) {
#ifdef DEBUG
	 DLDdbg << DLD_LIB_PREFIX "movie pixmap" << endl << flush;
#endif
      pm = movie.framePixmap();
   }
   else {
#ifdef DEBUG
	 DLDdbg << DLD_LIB_PREFIX "normal pixmap" << endl << flush;
#endif
      pm = pix;
   }

   if(!pm.isNull()) {            
      QRect r = rect();
      int x, y, w, h;
      r.rect( &x, &y, &w, &h );
      if ( (isDown() || isOn()) && style() == WindowsStyle ) {
	 // shift pixmap/text
	 x++;
	 y++;
	 pressed = true;
      }
      int px, py;

      if(!bigpic) {      
	 x += pm.width()+12;  y += 2;  w -= 14+pm.width();  h -= 4;
	 QRect br = p->boundingRect( x, y, w, h, AlignCenter|ShowPrefix, text(), -1 );
	 px = br.x() - pm.width() - 10;
	 py = (height() - pm.height())/2 + pressed;
      }
      else {
	 x += 2;  y += pm.height()+7;  w -= 4;  h -= pm.height()+9;
	 QRect br = p->boundingRect( x, y, w, h, AlignCenter|ShowPrefix, text(), -1 );
	 px = (width() - pm.width())/2 + pressed;
	 py = br.y() - pm.height() - 5;
      }

      if(! area.isNull() ) {
	 p->setClipRect(area.x()+px, area.y()+py, 
			area.width(), area.height() );
      }
      else {
	 p->setClipRect(px, py, pm.width(), pm.height() );
      }
      
      p->drawPixmap(px, py, pm);
   }
}

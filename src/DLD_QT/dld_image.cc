/******************************************************************************
**
** $Id: dld_image.cc,v 1.1 2001/03/14 02:33:12 saturn_de Exp $
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
#include "dld_image.h"
#include "dld_dialog.h"
#ifdef HAVE_QIMGIO
#include <qpngio.h>
#endif
#include <qpainter.h>
#include <qbitmap.h>
#include <iostream.h>

DLD_QTImage::DLD_QTImage (QWidget *_parent, 
			    const string& name, DLD_QTDialog *pd):
   QWidget (_parent),
   DLD_QTObj (name, pd)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "image " << dld_name 
	  << " constructed " << endl
	  << flush;
#endif
   fixed_height = fixed_width = true;
#ifdef HAVE_QIMGIO
   qInitPngIO (); 
#endif
#ifdef DEBUG
   DLDdbg << " constructed." << endl << flush;
#endif  
}

DLD_QTImage::
~DLD_QTImage ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "image deleted\n";
#endif
}

void DLD_QTImage::
create ()
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "image loading " << dld_name << endl
	  << flush;
#endif

   if(is_movie) {
      movie = QMovie(dld_name.c_str());
      
      if(movie.isNull()) {
	 getPixmap();
      }
      else {
	 movie.setBackgroundColor(backgroundColor());
	 movie.connectStatus(this, SLOT(movieStatus(int)));
	 movie.connectUpdate(this, SLOT(movieUpdate(const QRect&)));
	 movie.connectResize(this, SLOT(movieResized(const QSize&)));      
      }
   }
   else {
      getPixmap();
   }

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "image filling." << endl << flush;
#endif

//   pix.fill(this, 0, 0);

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "image filled." << endl << flush;
#endif

/*   setFixedWidth (p.width ());
   setFixedHeight (p.height ());
*/
//   repaint();
   DLD_Obj::create();
}


void DLD_QTImage::paintEvent( QPaintEvent *e)
{
   QPainter paint( this );   
   paint.setClipRect(e->rect());

   QPixmap pm;

   if(is_movie)
      pm = movie.framePixmap();
   else
      pm = pix;

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "image paintEvent." << endl << flush;
#endif      
   
   paint.drawPixmap(0, 0, pm);
}

void DLD_QTImage::getPixmap()
{
   pix.load(dld_name.c_str());
   if(pix.isNull())
      DLDerr << "image " << dld_name << _(" could not be loaded")
	     << endl << flush;
   else {
      setFixedWidth (pix.width ());
      setFixedHeight (pix.height ());
      repaint();
   }
}

void DLD_QTImage::movieStatus( int status)
{
   if (status < 0) {
      movie.disconnectStatus(this, SLOT(movieStatus(int)));
      movie.disconnectUpdate(this, SLOT(movieUpdate(const QRect&)));
      movie.disconnectResize(this, SLOT(movieResized(const QSize&)));      
      getPixmap();
   }
   else is_movie = true;
}

void DLD_QTImage::movieUpdate( const QRect& area)
{
   QRect r = rect();
/*   
   if ( r.size() != movie.framePixmap().size() ) {
      // Need to scale - redraw whole frame.
      repaint( r );
   } else {
*/
      // Only redraw the changed area of the frame
      repaint( area.x()+r.x(), area.y()+r.y(),
	       area.width(), area.height() );
//   }

}

void DLD_QTImage::movieResized(const QSize& size)
{
   // The movie changed size, probably from its initial zero size.
   resize( size.width() , size.height() );
   setFixedWidth (size.width ());
   setFixedHeight (size.height ());
}

/******************************************************************************
**
** $Id: dld_dialog.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#include "qobjectlist.h"
#include "dld_qtlib.h"
#include "dld_dialog.h"
#include "dld_qtapp.h"
#include <iostream.h>

DLD_QTDialog:: 
DLD_QTDialog (const string& _name, DLD_QTApp *_app, const DLD_Out _out):
   QDialog (0, convstr(_name).c_str(), FALSE, WStyle_Title),
   DLD_QTContainer(_name, _app, this),
   DLD_QTObj (_name, this),
   DLD_Dialog(_app, _out),
   init_size(0,0,0,0)
{

//   toplayout = new QGridLayout (this, 1, 1, QT_BORDER, QT_BORDER);
   toplayout = new QVBoxLayout (this, QT_BORDER, QT_BORDER);
   
   dld_rows = 0;
   setCaption (_name.c_str());
   pardia = this;
   qwidget = this;
   empty = true;
   first_time = true;
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "dialog " << dld_name << " constructed" 
	  << endl << flush;
#endif
/*
  menu = new QMenuBar(this);
  toplayout->addWidget(menu);
*/
}

DLD_QTDialog::
~DLD_QTDialog ()
{
   dld_app->del_child(this);

#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "dialog " << dld_name << " delete";
   DLDdbg.flush ();
#endif
}

void DLD_QTDialog::setGeometry ( int x, int y, int w, int h )
{
   // QDialog::setGeometry ( x, y, w, h );
   init_size = QRect(x,y,w,h);
}

void DLD_QTDialog::
create ()
{
   if(is_created)
      return;

   printvars = true;

   setUpdatesEnabled( FALSE );

   int nullanz=0, sum=0;
   for(int i = 0; i < dld_rows; i++)
   {
      if(!qtobjs[i])
	 continue;
      int p = qtobjs[i]->obj_heightP;
      if(p)
	 sum += p;
      else
	 nullanz++;
   }
   sum = (sum && (sum < 100)) ? 100 - nullanz : nullanz;

   for(int i = 0; i < dld_rows; i++)
   {
      if(!qtobjs[i])
	 continue;
      int p = qtobjs[i]->obj_heightP;
      if(p)
	 toplayout->setStretchFactor(qtwidgets[i], p);
      else {
	 if(qtobjs[i]->fixed_height)
	    toplayout->setStretchFactor(qtwidgets[i], 0);
	 else
	    toplayout->setStretchFactor(qtwidgets[i], sum / nullanz);
      }
   }

   DLD_QTContainer::create();

   toplayout->activate ();

   if(init_size.isNull()) {
      init_size = geometry();
      resize((obj_widthP) ? init_size.width() * obj_widthP / 100 
	     : sizeHint().width(),
	     (obj_heightP) ? init_size.height() * obj_heightP / 100 
	     : sizeHint().height());
      init_size = geometry();
   } else {
      resize((obj_widthP) ? init_size.width() * obj_widthP / 100 
	     : init_size.width(),
	     (obj_heightP) ? init_size.height() * obj_heightP / 100 
	     : init_size.height());

      if ( children() ) {
	 QObjectListIt it(*children());
	 register QObject *object;
	 QWidget *widget;
	 while ( it ) {				// show all widget children
	    object = it.current();		//   (except popups)
	    ++it;
	    if ( object->isWidgetType() ) {
	       widget = (QWidget*)object;
	       widget->show();
	    }
	 }
      }
   }   

   if(first_time) {
      // Window-Manager soll Fenster plazieren, deshalb raus:
      // move(init_size.x(), init_size.y());
      first_time = false;
   }

   setUpdatesEnabled( TRUE );
   show ();      

   is_created = true;
   DLD_Obj::create();
}

void DLD_QTDialog::
insert (QWidget * w, DLD_QTObj * obj)
{
#ifdef DEBUG
   DLDdbg << DLD_LIB_PREFIX "dialog add widget at row " << dld_rows << endl << flush;
#endif

//   toplayout->expand(dld_rows+1, 1);

   toplayout->addWidget (w);
//   toplayout->addWidget (w, dld_rows, 0, AlignCenter);
   qtobjs[dld_rows] = obj;
   qtwidgets[dld_rows] = w;
   dld_rows++;
   empty = false;
}

void DLD_QTDialog::
done (int w)
{
   DLDdbg << "qt_dialog done(" << w << ") called" << endl << flush;

   emit has_exited();

   if(dld_app->mainDialog != this) {
      QDialog::done(w);
      delete this;
   } else {
      /*
       * Don't call done if we are the mainDialog,
       * cause it would delete us.
       */
//      QDialog::done(w);
      /* Don't call cleanup here */
//      cleanup();
   }    
};

int DLD_QTDialog::
set_name (const string& name)
{
   dld_name = name;
   setCaption (name.c_str());
   return 0;
}

void DLD_QTDialog::cleanup() 
{
//   init_size = geometry();

   setUpdatesEnabled( FALSE );

   // Clean up childlist
   for(CI i = childlist.begin(); i != childlist.end(); i = childlist.begin()) {
      delete *i;
   }

   delete toplayout;

   toplayout = new QVBoxLayout (this);

   setUpdatesEnabled( TRUE );

   toplayout->activate ();

   repaint();

//   setUpdatesEnabled( FALSE );
   dld_rows = 0;

   // Clean up dld_name
   dld_name.erase();

   is_created = false;
   empty = true;

   DLD_Dialog::close();
   out.flush();
}

void DLD_QTDialog::closeEvent ( QCloseEvent * e)
{
   printvars = false;
   if(dld_app->mainDialog == this) {
      /* 
       * Don't close the window,
       * if we are the main Dialog 
       */
      cleanup();
      emit has_exited();
   }
   else {
      QDialog::closeEvent(e);
   }
}

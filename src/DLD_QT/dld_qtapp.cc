/******************************************************************************
**
** $Id: dld_qtapp.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_qtapp.h"
#include "dld_dialog.h"
#include <qwidgetlist.h>
#include <signal.h>
#include <time.h>

DLD_QTApp::DLD_QTApp (const string&, int argc, char **argv) :
   QApplication (argc, argv)
{

#if QT_VERSION < 200
   setStyle(WindowsStyle);
#endif

   mainDialog = 0;
   running = false;
   connect (this, SIGNAL (lastWindowClosed(void)), 
	    this, SLOT (slot_has_exited (void)));
   signal(SIGCHLD, SIG_IGN);
}

DLD_QTApp::
~DLD_QTApp ()
{
   CI first = childlist.begin();
   CI last  = childlist.end();
   
   while(first != last)
   {
      if(*first) {
         delete *first;
      }
      first = childlist.begin();
      last  = childlist.end();
   }

   if(mainDialog)
      delete mainDialog;

#ifdef DEBUG
   DLDdbg << "->Closing<-\n";
   DLDdbg.flush ();
#endif
}

DLD_Dialog *DLD_QTApp::
dialog (const string& _name , const DLD_Out& _out)
{
   DLD_QTDialog *dia;

   if (mainDialog && mainDialog->isEmpty()){
      mainDialog->set_name(_name);
      mainDialog->out.init(_out);
      dia = mainDialog;
   }
   else {
      
      dia = new DLD_QTDialog (_name, this, _out);
      
#ifdef DEBUG
      DLDdbg << guiname << " created new dldialog" << endl << flush;
#endif   
      if(!mainDialog) {
	 connect (dia, SIGNAL (has_exited(void)), 
                  this, SLOT (slot_has_exited (void)));

	 mainDialog = dia;
	 setMainWidget( mainDialog );
	 init_size = mainDialog->frameGeometry();
      }
      else {
	 dia->init_size = init_size;
      }
   }

   add_child (dia);

#ifdef DEBUG
   DLDdbg << guiname << " added new dldialog " << _name << endl << flush;
#endif   

   return dia;
}

int DLD_QTApp::
exec ()
{
   if(!running && mainDialog && mainDialog->was_created()) {
      print_status ("->Running<-");
      running = true;
/*
  QWidgetList  *list = QApplication::topLevelWidgets();
  QWidgetListIt it( *list );  // iterate over the widgets
  while ( it.current() ) {    // for each top level widget...
  if ( !it.current()->isVisible() )
  it.current()->show();
  ++it;
  }
  delete list; // delete the list, not the widgets
*/  
      while(running) {
	 clock_t start, stop;
	 start = clock(); 
	 QApplication::processEvents(100);
         stop = clock();
         if(running) {
            int tosleep = 100 - (stop - start) * 1000 / CLOCKS_PER_SEC;
            DLD_Gui::parse(tosleep*1000);
         }
      }

      QApplication::processEvents();

      // Must be here
      mainDialog->cleanup();

      CI first = childlist.begin();
      CI last  = childlist.end();
      
      while(first != last)
      {
	 if(*first) {
	    if(*first != mainDialog) {
	       (*first)->hide();
	       delete *first;
	    }
	    else {
	       childlist.erase(first);
	    }
	 }
	 first = childlist.begin();
	 last  = childlist.end();
      }
      print_status ("->Idle<-");   
      QApplication::processEvents();
   }
   else if(!running) {
      print_status ("->Idle Parsing<-");
      QApplication::processEvents();
      DLD_Gui::parse(-1);
   }

   return 0;
}

void DLD_QTApp::
slot_has_exited ()
{
   running = false;
}

void DLD_QTApp::
del_child(DLD_QTDialog *dia)
{
   CI first = childlist.begin();
   CI last = childlist.end();
   while (first != last) {
      if (*first == dia) {
	 // Remove it from the list
	 childlist.erase(first);

	 if(dia == mainDialog) {
	    /*
	     * First delete all other dialogs.
	     * This will get us here, but we already removed the mainDialog.
	     */
	    CI first = childlist.begin();
	    CI last  = childlist.end();	    
	    while(first != last)
	    {
/*	       (*first)->done(QDialog::Rejected);
	       QApplication::processEvents();
*/
	       delete (*first);
	       first = childlist.begin();
	       last  = childlist.end();
	    }
	 }       
	 break;
      }
      first++;
   }
}

int DLD_QTApp::
add_child (DLD_QTDialog * nobj)
{
   Assert(Bad_arg, nobj);

   childlist.push_back(nobj);

   return 0;
}

int DLD_QTApp::
print_status (const string &str)
{
#ifdef DEBUG
   DLDdbg << "status " << str << "\n";
   DLDdbg.flush ();
#endif

   return 0;
}

const string& DLD_QTApp::name(const string& newname)
{
   guiname = newname;
   
   if(mainDialog)
      mainDialog->set_name(newname);

   return guiname;
}

/******************************************************************************
**
** $Id: dld_tvapp.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TStatusLine
#define Uses_TBackground
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TKeys

#include <string.h>
#include <stdio.h>
#include <signal.h>

#include "dld_tvlib.h"
#include "dld_tvapp.h"
#include "dld_dialog.h"

static TStatusItem *statusItem = 0;

#define DLD_cpBackground "\x08"

#define cmDLDQuit 100

class DLD_TVDesktop : public virtual TDeskTop , public virtual TDeskInit 
{
public:
   DLD_TVDesktop( const TRect& bounds );

   static TBackground *initBackground( TRect r );
};

class DLD_TVBackground : public TBackground 
{
public:
   DLD_TVBackground( const TRect& bounds, char aPattern ) :
      TBackground(bounds,aPattern) {
   };

   TPalette& getPalette() const {
      static TPalette 
	 palette( DLD_cpBackground, sizeof( DLD_cpBackground )-1 );
      return palette;
   };
 
};


TBackground *DLD_TVDesktop::initBackground( TRect r ) 
{
   defaultBkgrnd = '\x20';
   return new DLD_TVBackground( r, defaultBkgrnd);
}

DLD_TVDesktop::DLD_TVDesktop( const TRect& bounds ) :
   TDeskTop(bounds ),
   TDeskInit( &DLD_TVDesktop::initBackground )
{
}


DLD_TVApp::
DLD_TVApp (const string&, int _oldsid, int, char **):
   TProgInit(&DLD_TVApp::initStatusLine, &DLD_TVApp::initMenuBar, 
	     &DLD_TVApp::initDeskTop),
   mainDialog(0),
   running(false),
   oldsid(_oldsid)
{
   /*
    * We don't wanna get stopped
    */
   signal(SIGTSTP, SIG_IGN);
   print_status ("->Starting<-");
}

DLD_TVApp::
~DLD_TVApp ()
{
#ifdef DEBUG
   DLDdbg << "tvapp  ending!" << endl << flush;
#endif
}

DLD_Dialog *DLD_TVApp::
dialog (const string& name, const DLD_Out& _out)
{
   print_status ("->Adding Dialog<-");

   DLD_TVDialog *p =  new DLD_TVDialog (conname(name), this, _out);

   add_child(p);

   if(!mainDialog)
      mainDialog = p;

   return p;
}

int DLD_TVApp::
exec ()
{
   if(!running && mainDialog) {
      print_status ("->Running<-");
      
      running = true;
/*
 * Obsoleted by setsid
 *      menuBar->draw();
 */
      run ();
      running = false;
      
      CI first = childlist.begin();
      CI last  = childlist.end();
      
      while(first != last)
      {
	 delete *first;
	 first = childlist.begin();
	 last  = childlist.end();
      }
      
      print_status ("->Idle<-");   
      mainDialog = 0;
   } 
   else if(!running) {
      DLD_Gui::parse(-1);
   }
     
   return 0;
}

void DLD_TVApp::
idle () 
{
   // DLD_Gui::idle for further parsing input, if any
//   if(running)
   if(!DLD_Gui::parse(100000)) {
      /* Now generate QUIT event */	    
      TEvent te;
      te.what = evCommand;
      te.message.command = cmQuit;
      te.message.infoPtr = 0;
      /*
       * needs fix in tvision to remove TProgram:: and call putEvent
       * directly.
       */
      TProgram::putEvent (te);      
   }

   // The native idle function for TApplications
   TApplication::idle();
}

TStatusLine *DLD_TVApp::
initStatusLine (TRect r)
{
   char *stptr = new char[21];

   sprintf (stptr, "%20s", " ->Starting<-");

   r.a.y = r.b.y - 1;

   return new TStatusLine (r,
			   *new TStatusDef (0, 0xFFFF) +
/*			   *new TStatusItem ("~Alt-X~ to Cancel!", 
			   kbAltX, cmDLDQuit) + */
			   *new TStatusItem (_("SPACE selects - TAB to move -"),
			   0, 0) +
			   *(statusItem = new TStatusItem (stptr, 0, 0)) +
			   *new TStatusItem (0, kbF10, cmMenu) +
			   *new TStatusItem (0, kbAltF3, cmClose) +
			   *new TStatusItem (0, kbF5, cmZoom) +
			   *new TStatusItem (0, kbCtrlF5, cmResize)
      );
}



int DLD_TVApp::
print_status (const string& str)
{
   if ((statusItem != 0) && (statusItem->text != 0))
   {
      strncpy (statusItem->text, str.c_str(), 20);
      statusLine->draw ();
   }

   return 0;
}

void DLD_TVApp::
del_child(DLD_TVDialog *dia)
{
   CI first = childlist.begin();
   CI last = childlist.end();
   while (first != last) {
      if (*first == dia) {
	 // Remove it from the list
	 childlist.erase(first);
	 deskTop->remove(*first);

	 if(dia == mainDialog) {
	    /*
	     * First delete all other dialogs.
	     * This will get us here, but we already removed the mainDialog.
	     */
	    CI first = childlist.begin();
	    CI last  = childlist.end();	    
	    while(first != last)
	    {
	       delete *first;
	       first = childlist.begin();
	       last  = childlist.end();
	    }

	    /* Now generate QUIT event */	    
	    TEvent te;
	    te.what = evCommand;
	    te.message.command = cmQuit;
	    te.message.infoPtr = 0;
	    /*
	     * needs fix in tvision to remove TProgram:: and call putEvent
	     * directly.
	     */
	    TProgram::putEvent (te);
	 }       
	 break;
      }
      first++;
   }
}

int DLD_TVApp::
add_child (DLD_TVDialog * nobj)
{
   Assert(Bad_arg, nobj);

   childlist.push_back(nobj);

   return 0;
}

void DLD_TVApp::
handleEvent( TEvent& event )
{
   TApplication::handleEvent( event );
   if (event.what == evCommand)
   {
      switch (event.message.command)
      {	 
      case cmTile:             //  Tile current file windows
	 deskTop->tile(deskTop->getExtent());
	 break;
	 
      case cmCascade:          //  Cascade current file windows
	 deskTop->cascade(deskTop->getExtent());
	 break;
	 
      case cmDLDQuit:
	 delete mainDialog;
	 break;

      default:                    //  Unknown command
	 return;
	 
      }
      clearEvent (event);
   }
}   


TMenuBar * DLD_TVApp::initMenuBar(TRect r)
{
/*    TSubMenu& sub2 =
      *new TSubMenu( "~F~ile", 0, hcFile ) +
        *new TMenuItem( "E~x~it", cmQuit, kbAltX, hcFExit, "Alt-X" );
*/
    TSubMenu& sub3 =
      *new TSubMenu( "~W~indows", 0, hcWindows ) +
        *new TMenuItem( "~R~esize/move", cmResize, kbCtrlF5, hcWSizeMove, "Ctrl-F5" ) +
        *new TMenuItem( "~Z~oom", cmZoom, kbF5, hcWZoom, "F5" ) +
        *new TMenuItem( "~N~ext", cmNext, kbF6, hcWNext, "F6" ) +
        *new TMenuItem( "~C~lose", cmClose, kbAltF3, hcWClose, "Alt-F3" ) +
        *new TMenuItem( "~T~ile", cmTile, kbNoKey, hcWTile ) +
        *new TMenuItem( "C~a~scade", cmCascade, kbNoKey, hcWCascade );

    r.b.y =  r.a.y + 1;
    return (new TMenuBar( r, sub3) );
//    return (new TMenuBar( r, sub2 + sub3) );
}

TDeskTop *DLD_TVApp::initDeskTop( TRect r )
{
    r.a.y++;
    r.b.y--;
    return new DLD_TVDesktop( r );
/*    TDeskTop::defaultBkgrnd = '\x20';
    return new TDeskTop( r );
*/
}

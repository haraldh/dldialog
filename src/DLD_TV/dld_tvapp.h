/******************************************************************************
**
** $Id: dld_tvapp.h,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_TVAPP_H
#define DLD_TVAPP_H

#include "dld_tvlib.h"
#include "../dld_gui.h"
#include "dld_tvobj.h"
#define Uses_TRect
#define Uses_TDialog
#define Uses_TGroup
#define Uses_TDeskTop
#define Uses_TRect
#define Uses_TApplication
#include <tvision/tv.h>

class DLD_TVDialog;
class TStatusItem;

const int cmOpenCmd     = 105;
const int cmDOS_Cmd     = 107;

const int
  hcCancelBtn            = 35,
  hcFDosShell            = 16,
  hcFExit                = 17,
  hcFOFileOpenDBox       = 31,
  hcFOFiles              = 33,
  hcFOName               = 32,
  hcFOOpenBtn            = 34,
  hcFOpen                = 14,
  hcFile                 = 13,
  hcNocontext            = 0,
  hcOCColorsDBox         = 39,
  hcOColors              = 28,
  hcOMMouseDBox          = 38,
  hcOMouse               = 27,
  hcORestoreDesktop      = 30,
  hcOSaveDesktop         = 29,
  hcOpenBtn              = 36,
  hcOptions              = 26,
  hcPuzzle               = 3,
  hcSAbout               = 8,
  hcSAsciiTable          = 11,
  hcSCalculator          = 12,
  hcSCalendar            = 10,
  hcSPuzzle              = 9,
  hcSystem               = 7,
  hcViewer               = 2,
  hcWCascade             = 22,
  hcWClose               = 25,
  hcWNext                = 23,
  hcWPrevious            = 24,
  hcWSizeMove            = 19,
  hcWTile                = 21,
  hcWZoom                = 20,
  hcWindows              = 18;


/** the tvision implementation of DLD_Gui.
 *
 *	@author	        Harald Hoyer
 *	@version	$Version$
 */
class DLD_TVApp : public DLD_Gui, public TApplication
{
public:
   /// Constructor
   DLD_TVApp (const string& name, int oldsid, int argc, char **argv);

   /// Destructor
   virtual ~DLD_TVApp ();
   
   /// Virtual function.
   virtual DLD_Dialog *dialog (const string& name , const DLD_Out& out);
   
   /// Virtual function.x
   virtual int exec ();

   /// Virtual function.
   const string& name (const string& newname) {
      guiname = newname;
      return guiname;
   };

   /// Virtual function.
   const string& name () {
      return guiname;
   };

   /// Virtual function.
   virtual int print_status (const string& text);

   void idle();

   void del_child(DLD_TVDialog *dia);

   int add_child (DLD_TVDialog * nobj);

   void handleEvent( TEvent& event );

   ///
   DLD_TVDialog *mainDialog;

private:
///
   string guiname;

   ///
   static TStatusLine *initStatusLine( TRect r );
   ///
   static TMenuBar  *initMenuBar( TRect r );
   
   static TDeskTop *initDeskTop( TRect r );

   typedef DLD_TVDialog *DLD_TVDialog_Ptr;
   list<DLD_TVDialog_Ptr>  childlist;
   bool childlock;
   typedef list<DLD_TVDialog_Ptr>::iterator CI; 

   bool running;
   int oldsid;
};

#endif

/******************************************************************************
**
** $Id: dld_combobox.h,v 1.1 2001/03/14 02:33:14 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_TVCOMBOBOX_H
#define DLD_TVCOMBOBOX_H

#define Uses_TComboBox
#define Uses_TStaticInputLine
#define Uses_TStringCollection 

#include "../dld_combobox.h"
#include "dld_tvobj.h"

#include "tcombobx.h"
#include "tsinputl.h"
#include <map>

class DLD_NTVComboBox : public TComboBox
{
public:
   DLD_NTVComboBox(const TRect& bounds, TStaticInputLine *aLink, TCollection *aList):
      TComboBox(bounds,aLink,aList), enabled(true) { geom = bounds;};

   virtual ~DLD_NTVComboBox() {};

   void setGeom(const TRect& _geom) { 
      geom = _geom;
      geom.a.x = geom.b.x - 1; 
   };

   void disable() {enabled = false; };
   void handleEvent( TEvent& event ) { 
      if(enabled) 
	 TComboBox::handleEvent(event);
   };


   /// empty 
   void create() ;

   void calcBounds(TRect& bounds, TPoint) { bounds = geom; }; 

private:
   TRect geom;
   bool enabled;
};

class DLD_TVComboItem;

/**
 * Abstract Interface
 * @short Abstract Interface
 * @author Harald Hoyer <HarryH@Royal.Net>
 */
class DLD_TVComboBox : public DLD_TVObj,
		       public DLD_ComboBox, 		       
		       public TStaticInputLine 
{
public:
   DLD_TVComboBox(const string& _name, DLD_TVDialog *parent);
   
   ~DLD_TVComboBox();
   
   /** Adds a comboitem to the combobox.
    * @param name The text of the item
    * @return ptr to item
    */
   DLD_ComboItem *comboitem(const string& = 0);
   
   /** Indicates the beginning of a new block
    *
    * Can be used to reserve space for children.
    */
   void open_brace() {};

   /** Indicates the end of a block.
    *
    * Can be used to collect all children.
    */
   void close_brace() {};
   
   void create();
   
   void changeBounds( const TRect& bounds );
   
   void calcBounds(TRect& bounds, TPoint delta );
   
   void setGeom( const TRect& geom );

   void newData(char *);

   void handleEvent( TEvent& event );
   
private:
   TStringCollection ilist;
   DLD_NTVComboBox *ibox;
   map<string, DLD_TVComboItem *>itemmap;
   typedef map<string, DLD_TVComboItem *>::iterator IMI;
   int item_nr;
};
#endif

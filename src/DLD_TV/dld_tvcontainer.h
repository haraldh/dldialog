/******************************************************************************
**
** $Id: dld_tvcontainer.h,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_TVCONTAINER_H
#define DLD_TVCONTAINER_H
#include <string>
#include <list>
#include "../dld_container.h"
#include "dld_tvobj.h"

#define Uses_TView
#include <tvision/tv.h>

class DLD_TVApp;
class DLD_TVDialog;
class DLD_TVObj;


/** TV implementation of the DLD_Container class
 *
 */
class DLD_TVContainer: public virtual DLD_TVObj, 
		       public virtual DLD_Container 
{
public:

   /** Orientation flag.
    * <ul>
    * <li>O_HOR Horizontal orientation (DLD_ROW)
    * <li>O_VER Vertical orientation (DLD_COL)
    * </ul>
    */
   enum orient_t {
      O_HOR, 
      O_VER  
   };

   /** Constructor.
    * @param _name The name of the container.
    * @param _app  The parent application.
    * @param _pd   The parent dialog
    * @param _orient The orientation of the container, if any.
    */
   DLD_TVContainer(const string& _name, 
		   DLD_TVApp *_app, DLD_TVDialog *_pd,
		   orient_t _orient);

   /// Destructor.
   virtual ~DLD_TVContainer() ;
   
   /// Pure virtual function.
   virtual DLD_Dialog *dialog (const string& _name = 0);

   /// Pure virtual function.
   virtual DLD_Form * form (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_Col * col (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_Row * row (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_List * list (const string& _name = 0) ;

   /// Pure virtual function.
   virtual DLD_CheckList * checklist (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_RadioList * radiolist (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_ComboBox * combobox (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_Text * text (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_Button * button (const string& _name = 0) ;

   /// Pure virtual function.
   virtual DLD_Gauge * gauge (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_TextBox * textbox (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_Input * input (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_Image * image (const string& name = 0) ;

   /// Pure virtual function.
   virtual DLD_Menu * menu (const string& name = 0, bool = false) ;

   /// Pure virtual function.
   virtual void open_brace() ;

   /// Pure virtual function.
   virtual void close_brace() ;

   /// Pure virtual function.
   virtual void create() ;

   /** Delete a possible child from the childlist
    * @param obj A DLD_TVObj, that may be a child of this container.
    */
   void del_child(DLD_TVObj * obj);

   /** Changes this widgets geometry.
    * @param _bounds The new bounds.
    */
   virtual void changeBounds(const TRect& _bounds);

   /** Sets this widgets geometry.
    * Used as from this Containers class to set the geometry to DLD_TVObj's.
    * @param _bounds The new bounds.
    */
   void setGeom(const TRect& _bounds) { geom = _bounds; changeBounds(geom); };


   /// The parent DLD_TVApp application.
   DLD_TVApp *app;

   const string &context(const string& _name, int& twidth, int& theight);

private:
   /** The containers orientation.
    */
   orient_t orient;

   /// Pure virtual function.
   virtual void insert(TView *p) =0;

   /** Add a child to the container.
    * @param nobj A pointer to a DLD_TVObj.
    */
   void add_child (DLD_TVObj * nobj);
};

#endif


/******************************************************************************
**
** $Id: dld_qtcontainer.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/

#ifndef DLD_QTCONTAINER_H
#define DLD_QTCONTAINER_H

#include "../dld_container.h"
#include "dld_qtobj.h"
#include <string>
#include <list>

/** QT implementation of the DLD_Container class
 *
 */
class DLD_QTContainer: public virtual DLD_QTObj, 
		       public virtual DLD_Container
{
public:

   /** Constructor.
    * @param _name The name of the container.
    * @param _app  The parent application.
    * @param _pd   The parent dialog
    */
   DLD_QTContainer(const string& _name, 
		   DLD_QTApp *_app, DLD_QTDialog *_pd);

   /// Destructor.
   virtual ~DLD_QTContainer() ;
   
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
    * @param obj A DLD_QTObj, that may be a child of this container.
    */
   void del_child(DLD_QTObj * obj);

   /// The parent DLD_QTApp application.
   DLD_QTApp *dld_app;

   virtual void insert (QWidget * w, DLD_QTObj *) = 0;

protected:

   QWidget *qwidget;
};

#endif

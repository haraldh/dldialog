/******************************************************************************
**
** $Id: dld_container.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** by Harald Hoyer (dldialog@parzelle.de) 
** Copyright (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/


/******************************************************************************
 *
 * IMPORTANT:
 * ----------
 *
 * If you modify anything of this you have to modify 
 * GUI_VERSION_INFO in configure.in following the guidelines in
 * README.developers
 *
 *****************************************************************************/


#ifndef DLD_GUI_CONTAINER_H
#define DLD_GUI_CONTAINER_H

#include "dld_obj.h"

class DLD_Dialog;
class DLD_Image;
class DLD_ListItem;
class DLD_List;
class DLD_CheckButton;
class DLD_CheckList;
class DLD_RadioButton;
class DLD_RadioList;
class DLD_ComboItem;
class DLD_ComboBox;
class DLD_Text;
class DLD_Button;
class DLD_Gauge;
class DLD_TextBox;
class DLD_Input;
class DLD_Menu;
class DLD_Form;
class DLD_Col;
class DLD_Row;

/**
 * Abstract Interface for Container.
 * @short Abstract Interface
 * @author Harald Hoyer <dldialog@parzelle.de>
 */
class DLD_Container : public virtual DLD_Obj {
public:
   /** Add a new dialog to the container.
    * @param name a string
    */
   virtual DLD_Dialog *dialog (const string& name = 0) = 0;

   /** Add a new form to the container.
    * @param name a string
    */
   virtual DLD_Form * form (const string& name = 0) = 0;

   /** Add a new col to the container.
    * @param name a string
    */
   virtual DLD_Col * col (const string& name = 0) = 0;

   /** Add a new row to the container.
    * @param name a string
    */
   virtual DLD_Row * row (const string& name = 0) = 0;

   /** Add a new list to the container.
    * @param name a string
    */
   virtual DLD_List * list (const string& name = 0) = 0;

   /** Add a new checklist to the container.
    * @param name a string
    */
   virtual DLD_CheckList * checklist (const string& name = 0) = 0;

   /** Add a new radiolist to the container.
    * @param name a string
    */
   virtual DLD_RadioList * radiolist (const string& name = 0) = 0;

   /** Add a new combobox to the container.
    * @param name a string
    */
   virtual DLD_ComboBox * combobox (const string& name = 0) = 0;

   /** Add a new text to the container.
    * @param name a string
    */
   virtual DLD_Text * text (const string& name = 0) = 0;

   /** Add a new button to the container.
    * @param name a string
    */
   virtual DLD_Button * button (const string& name = 0) = 0;

   /** Add a new gauge to the container.
    * @param name a string
    */
   virtual DLD_Gauge * gauge (const string& name = 0) = 0;

   /** Add a new textbox to the container.
    * @param name a string
    */
   virtual DLD_TextBox * textbox (const string& name = 0) = 0;

   /** Add a new input to the container.
    * @param name a string
    */
   virtual DLD_Input * input (const string& name = 0) = 0;

   /** Add a new PNG image to the container.
    * @param name the filename of the image in PNG format
    */
   virtual DLD_Image * image (const string& name = 0) = 0;

   /** Add a new menu to the container.
    * @param name a string
    */
   virtual DLD_Menu * menu (const string& name = 0, bool check = false) = 0;

   /** Indicates the beginning of a new block
    *
    * Can be used to reserve space for children.
    */
   virtual void open_brace() = 0;

   /** Indicates the end of a block.
    *
    * Can be used to collect all children.
    */
   virtual void close_brace() = 0;
};
#endif

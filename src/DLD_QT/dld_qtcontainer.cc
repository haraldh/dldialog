/******************************************************************************
**
** $Id: dld_qtcontainer.cc,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de>
**
******************************************************************************/
#include "dld_qtapp.h"
#include "dld_qtcontainer.h"
#include "dld_dialog.h"
#include "dld_button.h"
#include "dld_text.h"
#include "dld_row.h"
#include "dld_form.h"
#include "dld_col.h"
#include "dld_list.h"
#include "dld_checklist.h"
#include "dld_radiolist.h"
#include "dld_textbox.h"
#include "dld_combobox.h"
#include "dld_gauge.h"
#include "dld_input.h"
#include "dld_image.h"

DLD_QTContainer::
DLD_QTContainer(const string& _name, DLD_QTApp *_app, DLD_QTDialog *pd) :
   DLD_QTObj(_name, pd),
   dld_app(_app)
{
#ifdef DEBUG
   DLDdbg << "QTContainer " << dld_name << " constructed." << endl;
#endif
}

DLD_QTContainer::
~DLD_QTContainer() 
{
}
   
DLD_Dialog *DLD_QTContainer::
dialog (const string& _name = 0) 
{
   DLD_QTDialog *p = new DLD_QTDialog(_name, dld_app, pardia->out);
   dld_app->add_child(p);
   return p;
}

DLD_Form * DLD_QTContainer::
form (const string& name) 
{
    DLD_QTForm *p = new DLD_QTForm(qwidget, name, dld_app, pardia);
    insert(p, p);
    add_child(p);
    return p;
}

DLD_Col * DLD_QTContainer::
col (const string& name) 
{
    DLD_QTCol *p = new DLD_QTCol(qwidget, name, dld_app, pardia);
    insert(p, p);
    add_child(p);
    return p;
}

DLD_Row * DLD_QTContainer::
row (const string& name) 
{
    DLD_QTRow *p = new DLD_QTRow(qwidget, name, dld_app, pardia);
    insert(p, p);
    add_child(p);
    return p;
}

DLD_List * DLD_QTContainer::
list (const string& name) 
{
    DLD_QTList *p = new DLD_QTList(qwidget, name, pardia);
    add_child(p);
    insert(p, p);
    return p;
}

DLD_CheckList * DLD_QTContainer::
checklist (const string& name) 
{
    DLD_QTCheckList *p = new DLD_QTCheckList(qwidget, name, pardia);
    add_child(p);
    insert(p, p);
    return p;
}

DLD_RadioList * DLD_QTContainer::
radiolist (const string& name) 
{
    DLD_QTRadioList *p = new DLD_QTRadioList(qwidget, name, pardia);
    add_child(p);
    insert(p, p);
    return p;
}

DLD_ComboBox * DLD_QTContainer::
combobox (const string& name) 
{
   DLD_QTComboBox *p = new DLD_QTComboBox(qwidget, name, pardia);
   add_child(p);
   insert(p, p);
   return p;
}

DLD_Text * DLD_QTContainer::
text (const string& _name)
{
   DLD_QTText *p = new DLD_QTText(qwidget, _name, pardia);
   add_child(p);
   insert(p, p);
   return p;
}

DLD_Button * DLD_QTContainer::
button (const string& _name) 
{
   DLD_QTButton *p = new DLD_QTButton(qwidget, _name, pardia);
   add_child(p);
   insert(p, p);
   return p;
}

DLD_Gauge * DLD_QTContainer::
gauge (const string& _name)
{
    DLD_QTGauge *p = new DLD_QTGauge(qwidget, _name, pardia);
    add_child(p);
    insert(p, p);
    return p;
}

DLD_TextBox * DLD_QTContainer::
textbox (const string& _name)
{
    DLD_QTTextBox *p = new DLD_QTTextBox(qwidget, _name, pardia);
    add_child(p);
    insert(p, p);
    return p;
}

DLD_Input * DLD_QTContainer::
input (const string& _name)
{
    DLD_QTInput *p = new DLD_QTInput(qwidget, _name, pardia);
    add_child(p);
    insert(p, p);
    return p;
}

DLD_Image * DLD_QTContainer::
image (const string& _name)
{
    DLD_QTImage *p = new DLD_QTImage(qwidget, _name, pardia);
    add_child(p);
    insert(p, p);
    return p;
}

DLD_Menu * DLD_QTContainer::
menu (const string&, bool) 
{
    /* TODO */
    DLDerr << "menu: not yet implemented\n" << endl;
    Assert(Bad_arg, 0);
    return 0;
}

void DLD_QTContainer::
open_brace() 
{
}

void DLD_QTContainer::
close_brace() 
{
}

void DLD_QTContainer::
create() 
{
   if (is_created)
      return;

   for(CI i = childlist.begin(); i != childlist.end(); ++i) {
      (*i)->create ();
   }
   DLD_Obj::create();
}

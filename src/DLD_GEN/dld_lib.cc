/******************************************************************************
**
** $Id: dld_lib.cc,v 1.1 2001/03/14 02:33:07 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de>
**
******************************************************************************/
#include "../dld_lib.h"
#include "dld_gengui.h"

DLD_GENDialog::DLD_GENDialog(DLD_GENGui *parent, const DLD_Out _out) :
   DLD_GENObj(this), 
   DLD_GENContainer(this), DLD_Dialog(parent, _out),
   out(_out), app(parent) 
{
   DLDdbg << "Creating dialog" << endl;
   printvars = true;
};

DLD_GENDialog::~DLD_GENDialog() 
{
   DLDdbg << "Destroying dialog" << endl;
};

DLD_Dialog *DLD_GENContainer::dialog (const string& name) 
{
   DLD_GENDialog *p=new DLD_GENDialog(pd->app,pd->out);
   pd->app->childs.push(p);
   DLDdbg << name;
   return p;
};

DLD_Form * DLD_GENContainer::form (const string& name) 
{
   DLDdbg << name;DLD_GENForm *p = new DLD_GENForm(pd);add_child(p);return p;
};

DLD_Col * DLD_GENContainer::col (const string& name) 
{
   DLDdbg << name;DLD_GENCol *p = new DLD_GENCol(pd);add_child(p);return p;
};

DLD_Row * DLD_GENContainer::row (const string& name) 
{
   DLDdbg << name;DLD_GENRow *p =  new DLD_GENRow(pd);add_child(p);return p;
};

DLD_List * DLD_GENContainer::list (const string& name) 
{
   DLDdbg << name;DLD_GENList *p =  new DLD_GENList(pd);add_child(p);return p;
};

DLD_CheckList * DLD_GENContainer::checklist (const string& name) 
{
   DLDdbg << name;DLD_GENCheckList *p =  new DLD_GENCheckList(pd);add_child(p);return p;
};

DLD_RadioList * DLD_GENContainer::radiolist (const string& name) 
{
   DLDdbg << name;DLD_GENRadioList *p =  new DLD_GENRadioList(pd);add_child(p);return p;
};

DLD_ComboBox * DLD_GENContainer::combobox (const string& name ) 
{
   DLDdbg << name;DLD_GENComboBox *p =  new DLD_GENComboBox(pd);add_child(p);return p;
};

DLD_Text * DLD_GENContainer::text (const string& name ) 
{
   DLDdbg << name;DLD_GENText *p =  new DLD_GENText(pd);add_child(p);return p;
};

DLD_Button * DLD_GENContainer::button (const string& name ) 
{
   DLDdbg << name;DLD_GENButton *p =  new DLD_GENButton(pd);add_child(p);return p;
};

DLD_Image * DLD_GENContainer::image (const string& name ) 
{
   DLDdbg << name;DLD_GENImage *p =  new DLD_GENImage(pd);add_child(p);return p;
};

DLD_Gauge * DLD_GENContainer::gauge (const string& name ) 
{
   DLDdbg << name;DLD_GENGauge *p =  new DLD_GENGauge(pd);add_child(p);return p;
};

DLD_TextBox * DLD_GENContainer::textbox (const string& name ) 
{
   DLDdbg << name;DLD_GENTextBox *p =  new DLD_GENTextBox(pd);add_child(p);return p;
};

DLD_Input * DLD_GENContainer::input (const string& name ) 
{
   DLDdbg << name;DLD_GENInput *p =  new DLD_GENInput(pd);add_child(p);return p;
};

DLD_Menu * DLD_GENContainer::menu (const string& name , bool) 
{
   DLDdbg << name;DLD_GENMenu *p =  new DLD_GENMenu(pd);add_child(p);return p;
};

DLD_GENContainer::DLD_GENContainer(DLD_GENDialog *parent) : 
   DLD_GENObj(parent), pd(parent) 
{
};

DLD_GENContainer::~DLD_GENContainer() {};

DLD_GENObj::DLD_GENObj(DLD_Dialog *parent)
{
   set_dialog(parent);
   DLDdbg << "Creating obj" << endl;
};
   
DLD_GENObj::~DLD_GENObj()
{
   DLDdbg << "Destroying obj" << endl;
}; 

void DLD_GENObj::set_exit(bool) {};

void DLD_GENObj::widthP (unsigned int) {};

void DLD_GENObj::heightP(unsigned int) {};

void DLD_GENObj::activate() {}


extern "C" DLD_Gui *
dld_lib_init (const char *name, int argc, char **argv)
{
   return (DLD_Gui *) new DLD_GENGui (name, argc, argv);
}

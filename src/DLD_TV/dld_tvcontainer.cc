/******************************************************************************
**
** $Id: dld_tvcontainer.cc,v 1.1 2001/03/14 02:33:19 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include "dld_input.h"
#include "dld_tvapp.h"
#include "dld_tvcontainer.h"
#include "dld_dialog.h"
#include "dld_row.h"
#include "dld_form.h"
#include "dld_col.h"
#include "dld_list.h"
#include "dld_checklist.h"
#include "dld_radiolist.h"
#include "dld_button.h"
#include "dld_text.h"
#include "dld_textbox.h"
#include "dld_combobox.h"
#include "dld_gauge.h"

DLD_TVContainer::
DLD_TVContainer(const string& _name, DLD_TVApp *_app, DLD_TVDialog *pd, 
		orient_t _orient) :
   DLD_TVObj(_name, pd),
   app(_app),
   orient(_orient)
{
   if(orient == O_HOR) {
      lenWidth.setSizeFlag(false);
      lenHeight.setSizeFlag(true);
   }
   else if(orient == O_VER) {
      lenWidth.setSizeFlag(true);
      lenHeight.setSizeFlag(false);
   }

#ifdef DEBUG
   DLDdbg << "TVContainer " << dld_name << " constructed." << endl;
#endif

};


DLD_TVContainer::
~DLD_TVContainer() 
{
};
   
DLD_Dialog *DLD_TVContainer::
dialog (const string& _name = 0) 
{
   DLD_TVDialog *p = new DLD_TVDialog(conname(_name), app, dia->out);
   app->add_child(p);
   return p;
};

DLD_Form * DLD_TVContainer::
form (const string& _name) 
{
   DLD_TVForm *p = new DLD_TVForm(conname(_name), app, dia);
   add_child(p);
   return p;
};

DLD_Col * DLD_TVContainer::
col (const string& _name) 
{
   DLD_TVCol *p = new DLD_TVCol(conname(_name), app, dia);
   add_child(p);
   return p;
};

DLD_Row * DLD_TVContainer::
row (const string& _name) 
{
   DLD_TVRow *p = new DLD_TVRow(conname(_name), app, dia);
   add_child(p);
   return p;
};

DLD_List * DLD_TVContainer::
list (const string& _name) 
{
   DLD_TVList *p = new DLD_TVList(conname(_name), dia);
   add_child(p);
   dia->insert(p);
   return p;
};

DLD_CheckList * DLD_TVContainer::
checklist (const string& _name) 
{
   DLD_TVCheckList *p = new DLD_TVCheckList(conname(_name), dia);
   add_child(p);
   dia->insert(p);
   return p;
};

DLD_RadioList * DLD_TVContainer::
radiolist (const string& _name) 
{
   DLD_TVRadioList *p = new DLD_TVRadioList(conname(_name), dia);
   add_child(p);
   dia->insert(p);
   return p;
};

DLD_ComboBox * DLD_TVContainer::
combobox (const string& _name) 
{
   DLD_TVComboBox *p = new DLD_TVComboBox(conname(_name), dia);
   add_child(p);
   dia->insert(p);
   return p;
};

const string &DLD_TVContainer::
context(const string& name, int& twidth, int& theight)
{
   const char *cstr;
   int len;

   theight = 1;
   twidth = 0;
   cstr = name.c_str();

   const char *ptr = cstr, *optr = cstr;
   
   ptr = strchr (ptr, '\n');
   
   while (0 != ptr)
   {
      len = strlen (optr) - strlen (ptr);
      theight++;
      twidth = (twidth > len) ? twidth : len;
      
      optr = ptr;
      ptr++;
      ptr = strchr (ptr, '\n');
   }
   
   len = strlen (optr);
   twidth = (twidth > len) ? twidth : len;
   return name;
} 

DLD_Text * DLD_TVContainer::
text (const string& _name)
{
   int theight, twidth;
   string name = context(conname(_name), twidth, theight);

   DLD_TVText *b = new DLD_TVText(name, dia, twidth, theight);
   dia->insert(b);
   add_child(b);
   return b;
};

DLD_Button * DLD_TVContainer::
button (const string& _name) 
{
   int theight, twidth;
   string name = context(conname(_name), twidth, theight);

   DLD_TVButton *b = new DLD_TVButton(name, dia, twidth, theight);
   dia->insert(b);
   add_child(b);
   return b;
};

DLD_Gauge * DLD_TVContainer::
gauge (const string& _name)
{
   DLD_TVGauge *p = new DLD_TVGauge(conname(_name), dia);
   dia->insert(p);
   add_child(p);
   return p;
};

DLD_TextBox * DLD_TVContainer::
textbox (const string& _name)
{
   DLD_TVTextBox *p = new DLD_TVTextBox(conname(_name), dia);
   dia->insert(p);
   add_child(p);
   return p;
};

DLD_Input * DLD_TVContainer::
input (const string& _name)
{
   DLD_TVInput *p = new DLD_TVInput(conname(_name), dia);
   dia->insert(p);
   add_child(p);
   return p;
};

DLD_Image * DLD_TVContainer::
image (const string& _name)
{
/*
   DLD_TVInput *p = new DLD_TVInput(conname(_name), dia);
   dia->insert(p);
   add_child(p);
   return p;
*/
   return 0;
};

DLD_Menu * DLD_TVContainer::
menu (const string&, bool) 
{
   /* TODO */
   DLDerr << "menu: not yet implemented\n" << endl;
   Assert(Bad_arg, 0);
   return 0;
};

void DLD_TVContainer::
open_brace() 
{
};

void DLD_TVContainer::
close_brace() 
{
};

void DLD_TVContainer::
create() 
{
   if (is_created)
      return;

   for(CI i = childlist.begin(); i != childlist.end(); ++i) {
      DLD_Obj *childptr = *i;
      childptr->create ();
   }

   is_created = true;
   DLD_Obj::create();
};

void DLD_TVContainer::
add_child (DLD_TVObj * nobj)
{
   Assert(Bad_arg, nobj != NULL);
   DLD_Container::add_child(nobj);

   lenWidth.addChild(&nobj->lenWidth);
   lenHeight.addChild(&nobj->lenHeight);
}

void DLD_TVContainer::
changeBounds(const TRect &bounds)
{
#ifdef DEBUG
   DLDdbg << "tvcontainer changeBounds(" << bounds.a.x << "," << bounds.a.y << ")"
	  << "(" << bounds.b.x << "," << bounds.b.y << ")"
	  << endl;

   DLDdbg << "tvcontainer(" << lenWidth.getMin() << "," << lenHeight.getMin() << ")" 
	  << endl << flush;
#endif

//   lenWidth.setPos(bounds.a.x);
//   lenHeight.setPos(bounds.a.y);
   long x = bounds.a.x;
   long y = bounds.a.y;
  
   long width = bounds.b.x - x;
   long height = bounds.b.y - y;

   if((height != lenHeight.getLen()) || (width != lenWidth.getLen())) {
      lenWidth.setPos(bounds.a.x);
      lenHeight.setPos(bounds.a.y);
      lenWidth.setSize(width);
      lenHeight.setSize(height);
   }

   for(CI i = childlist.begin(); i != childlist.end(); ++i) {
      DLD_TVObj *childptr = dynamic_cast<DLD_TVObj*>(*i);

      long h = childptr->lenHeight.getLen();
      long w = childptr->lenWidth.getLen();

      long dy = childptr->lenHeight.getPos();
      long dx = childptr->lenWidth.getPos();

#ifdef DEBUG
      DLDdbg << childptr->dld_name << " setGeom(" 
	     << dx << "," << dy << ")"
	     << "(" << dx+w << "," << dy+h << ")"
	     << endl << flush;
#endif
      
      childptr->setGeom(TRect(x+dx, y+dy, x+dx+w, dy+y+h));

   }
}

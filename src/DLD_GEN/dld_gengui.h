/******************************************************************************
**
** $Id: dld_gengui.h,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#ifndef DLD_GENGUI_H
#define DLD_GENGUI_H

#include "../dld_gui.h"
#include "../dld_button.h"
#include "../dld_checkbutton.h"
#include "../dld_checklist.h"
#include "../dld_col.h"
#include "../dld_combobox.h"
#include "../dld_comboitem.h"
#include "../dld_container.h"
#include "../dld_dialog.h"
#include "../dld_form.h"
#include "../dld_gauge.h"
#include "../dld_image.h"
#include "../dld_input.h"
#include "../dld_lib.h"
#include "../dld_list.h"
#include "../dld_listitem.h"
#include "../dld_menu.h"
#include "../dld_obj.h"
#include "../dld_out.h"
#include "../dld_parser.h"
#include "../dld_parser_yacc.h"
#include "../dld_radiobutton.h"
#include "../dld_radiolist.h"
#include "../dld_row.h"
#include "../dld_text.h"
#include "../dld_textbox.h"
#include <stack>

class DLD_GENObj : public virtual DLD_Obj {
public:
   DLD_GENObj(DLD_Dialog *parent);
   
   virtual ~DLD_GENObj(); 

   virtual void set_exit(bool flag);

   virtual void widthP (unsigned int _w);

   virtual void heightP(unsigned int _h);

   virtual void activate();
};

class DLD_GENListItem : public virtual DLD_ListItem , public virtual DLD_GENObj {
public:
   DLD_GENListItem(DLD_Dialog *parent) : DLD_GENObj(parent) {DLDdbg << "listitem" << endl;};
   virtual ~DLD_GENListItem() {DLDdbg << "~listitem" << endl;};
};

class DLD_GENList : public virtual DLD_List, public virtual DLD_GENObj {
public:
   DLD_GENList(DLD_Dialog *parent) : DLD_GENObj(parent) {DLDdbg << "list" << endl;};
   virtual ~DLD_GENList() {DLDdbg << "~list" << endl;};

   virtual DLD_ListItem * listitem (const string& name) {DLDdbg << name;DLD_GENListItem *p = new DLD_GENListItem(dialog);add_child(p);return p;};

   virtual void set_multi(bool) {} ;

   virtual void open_brace() {};

   virtual void close_brace() {};
};

class DLD_GENCheckButton : public virtual DLD_CheckButton, public virtual DLD_GENObj {
public:
   DLD_GENCheckButton(DLD_Dialog *parent) : DLD_GENObj(parent) {DLDdbg << "checkbutton" << endl;};
   virtual ~DLD_GENCheckButton() {DLDdbg << "~checkbutton" << endl;};
};

class DLD_GENCheckList : public virtual DLD_GENObj, public virtual DLD_CheckList {
public:
   DLD_GENCheckList(DLD_Dialog *parent) : DLD_GENObj(parent) {DLDdbg << "checklist" << endl;};
   virtual ~DLD_GENCheckList() {DLDdbg << "~checklist" << endl;};

   virtual DLD_CheckButton *checkbutton(const string&) {DLD_GENCheckButton *p = new DLD_GENCheckButton(dialog);add_child(p);return p;};

   virtual void open_brace() {};

   virtual void close_brace() {};
};

class DLD_GENRadioButton : public virtual DLD_GENObj, public  virtual DLD_RadioButton {
public:
   DLD_GENRadioButton(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENRadioButton() {};
};

class DLD_GENRadioList : public virtual DLD_GENObj, public virtual DLD_RadioList {
public:
   DLD_GENRadioList(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENRadioList() {};

   virtual DLD_RadioButton *radiobutton(const string&) {DLD_GENRadioButton *p = new DLD_GENRadioButton(dialog);add_child(p);return p;};

   virtual void open_brace() {};

   virtual void close_brace() {};
};

class DLD_GENComboItem : public virtual DLD_GENObj, public virtual DLD_ComboItem {
public:
   DLD_GENComboItem(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENComboItem() {};
};

class DLD_GENComboBox : public virtual DLD_GENObj , public virtual DLD_ComboBox {
public:
   DLD_GENComboBox(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENComboBox() {};

   virtual DLD_ComboItem *comboitem(const string&  = 0) {DLD_GENComboItem *p = new DLD_GENComboItem(dialog);add_child(p);return p;};

   virtual void open_brace() {};

   virtual void close_brace() {};
};

class DLD_GENText : public virtual DLD_GENObj, public virtual DLD_Text {
public:
   DLD_GENText(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENText() {};
};

class DLD_GENButton : public virtual DLD_GENObj, public virtual DLD_Button {
public:
   DLD_GENButton(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENButton() {};
};

class DLD_GENImage : public virtual DLD_GENObj, public virtual DLD_Image {
public:
   DLD_GENImage(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENImage() {};
};

class DLD_GENGauge : public virtual DLD_GENObj, public virtual DLD_Gauge {
public:
   DLD_GENGauge(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENGauge() {};
   void set_progress(int) {};
   void add_exec (const string&) {};
};

class DLD_GENTextBox : public virtual DLD_GENObj, public virtual DLD_TextBox {
public:
   DLD_GENTextBox(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENTextBox() {};

   virtual void set_filename(const string&) {};
};

class DLD_GENInput : public virtual DLD_GENObj, public virtual DLD_Input {
public:
   DLD_GENInput(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENInput() {};

   virtual void set_ip(bool) {};

   virtual void set_passwd(bool) {};

   virtual void set_numeric(bool) {};
   virtual void set_length(int) {};
};

class DLD_GENMenu : public virtual DLD_GENObj, public virtual DLD_Menu {
public:
   DLD_GENMenu(DLD_Dialog *parent) : DLD_GENObj(parent) {};
   virtual ~DLD_GENMenu() {};

   virtual void set_global(bool) {};
};

class DLD_GENDialog;

class DLD_GENContainer : public virtual DLD_GENObj, public virtual DLD_Container {
public:
   DLD_GENContainer(DLD_GENDialog *parent);
   virtual ~DLD_GENContainer();
   virtual DLD_Dialog *dialog (const string& name);
   virtual DLD_Form * form (const string& name);
   virtual DLD_Col * col (const string& name);
   virtual DLD_Row * row (const string& name);
   virtual DLD_List * list (const string& name);
   virtual DLD_CheckList * checklist (const string& named);
   virtual DLD_RadioList * radiolist (const string& name);
   virtual DLD_ComboBox * combobox (const string& name );
   virtual DLD_Text * text (const string& name );
   virtual DLD_Button * button (const string& name );
   virtual DLD_Gauge * gauge (const string& name );
   virtual DLD_TextBox * textbox (const string& name );
   virtual DLD_Input * input (const string& name );
   virtual DLD_Image * image (const string& name );
   virtual DLD_Menu * menu (const string& name , bool check = false);
   virtual void open_brace() {};
   virtual void close_brace() {};
   DLD_GENDialog *pd;
};

class DLD_GENGui;

class DLD_GENDialog : public DLD_GENContainer, public DLD_Dialog {
public:
   DLD_GENDialog(DLD_GENGui *parent, const DLD_Out _out);
   virtual ~DLD_GENDialog();
   DLD_Out out;
   DLD_GENGui *app;
};

class DLD_GENCol : public virtual DLD_GENObj, public virtual DLD_GENContainer, public virtual DLD_Col {
public:
   DLD_GENCol(DLD_GENDialog *_parent) : DLD_GENObj(_parent), 
                                    DLD_GENContainer(_parent) {};
   virtual ~DLD_GENCol() {};
};

class DLD_GENRow : public virtual DLD_GENObj, public virtual DLD_GENContainer, public virtual DLD_Row {
public:
   DLD_GENRow(DLD_GENDialog *parent) : DLD_GENObj(parent), 
                                    DLD_GENContainer(parent) {};
   virtual ~DLD_GENRow() {};
};

class DLD_GENForm : public virtual DLD_GENObj, public virtual DLD_GENContainer, public virtual DLD_Form {
public:
   DLD_GENForm(DLD_GENDialog *parent) : DLD_GENObj(parent), 
                                    DLD_GENContainer(parent) {};
   virtual ~DLD_GENForm() {};
};

class DLD_GENGui : public virtual DLD_Gui
{
public:
   DLD_GENGui(const char *, int , char **) {};
   ~DLD_GENGui() {};
   
   DLD_Dialog *dialog (const string&, const DLD_Out& _out) {
      DLD_GENDialog *p=new DLD_GENDialog(this, _out );
      childs.push(p);
      return p;
   };
   
   int exec () {
      while(DLD_Gui::parse(-1)) {
	 DLD_GENObj *p; 
	 while(!childs.empty()) {
	    p = childs.top();
	    delete p;
	    childs.pop();
	 }
      }
      cerr << "parsed" << endl << flush; 
      return 0;
   };
   
   const string& name (const string& newname) {return mname = newname;};
   const string& name () {return mname;};
   virtual int print_status (const string& txt) {cerr << txt << endl << flush; return 0;};
   stack<DLD_GENObj *> childs;

private:
   string mname;
};

#endif

%{/*-*- c++ -*-*/
/******************************************************************************
**
** $Id: dld_parser_yacc.yy,v 1.2 2002/04/04 12:29:57 saturn_de Exp $ 
**
** The Yacc File for DLDialog
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998 (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/
#define YYERROR_VERBOSE
#include "dld_parser.h"
#include "dldialog.h"
#include "dld_button.h"
#include "dld_checkbutton.h"
#include "dld_checklist.h"
#include "dld_col.h"
#include "dld_combobox.h"
#include "dld_comboitem.h"
#include "dld_container.h"
#include "dld_dialog.h"
#include "dld_form.h"
#include "dld_gauge.h"
#include "dld_gui.h"
#include "dld_image.h"
#include "dld_button.h"
#include "dld_input.h"
#include "dld_lib.h"
#include "dld_list.h"
#include "dld_listitem.h"
#include "dld_menu.h"
#include "dld_obj.h"
#include "dld_out.h"
#include "dld_parser.h"
#include "dld_parser_yacc.h"
#include "dld_radiobutton.h"
#include "dld_radiolist.h"
#include "dld_row.h"
#include "dld_text.h"
#include "dld_textbox.h"

#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <stack>

char DLD_line[YYLMAX];
long DLD_lineno=0, DLD_linepos=0;
int DLD_run = 0;
static DLD_Obj *obj;
static DLD_ComboBox *combobox;
static DLD_RadioList *radiolist;
static DLD_CheckList *checklist;
static DLD_List *listwidget;
static DLD_Container *container;
static DLD_Menu *menu;
static DLD_Image *image;
static DLD_Input *input;
static DLD_TextBox *textbox;
static DLD_Button *button;
static DLD_Dialog *dialog;
static stack<DLD_Container *> cont_stack;
static string DLD_Outpath;

%}

%token DLD_START DLD_STOP DLD_CLIENT DLD_ENV_END

/* parent objects */
%token DIALOG FORM LIST ROW COL CHECKLIST RADIOLIST COMBOBOX

/* child objects */
%token CHECKBUTTON RADIOBUTTON TEXT BUTTON GAUGE TEXTBOX IMAGE
%token MENUITEM MENUCHECK LISTITEM COMBOITEM INPUT 

/* other object */
%token VARIABLE

/* parameters */
%token ADD SET VAR EXEC FORK MULTI EXIT GLOBAL IMAGEFILE
%token IP NUMERIC PASSWD LENGTH WIDTH HEIGHT FILEARG
%token SIGN FONT SIZE BG FG DISABLE MOVIE MOVIEFILE

%token <dld_string> NAME VARNAME NUMBER VARIABLE

%type <dld_string> value constring name

%start servermode

%%

servermode: /* empty */
            | servermode DLD_CLIENT { 
                 // Clear all remaining environment variables
                 DLD_GUI->clear_env();
                 // Generate temporary filename
                 DLD_Outpath = tempnam(indir.c_str(), NULL);

		 if (mknod(DLD_Outpath.c_str(), 
		 	  S_IFIFO|S_IRUSR|S_IWUSR, 0) == -1) {
		    // We are unable to produce an output pipe
		    string err("mknod ");
		    err += DLD_Outpath + ':' + ' ';
		    err += strerror(errno);
		    DLDerr << err << endl << flush;
		    throw DLD_Pipe_Error();
		 }
		 // Tell the client where to get the output
                 DLDout << DLD_Outpath << endl << flush;
                 } '{' dialogscript '}' {
		    DLDdbg << "erasing outpath" << endl << flush;
		    DLD_Outpath.erase();
                 }
	    | servermode DLD_START { 
		 DLD_run++; 
		 DLDdbg << "++DLD_run = " << DLD_run << endl << flush;
		 DLDout << "ok;" << endl << flush; 
	        } ';'
	    | servermode DLD_STOP ';' { 
                 DLD_run--; 
		 if (DLD_run <= 0) {
		    DLDdbg << "DLD_run == 0" << endl << flush;
		    DLD_run = -1;
		    // Return from parsing
		    listen(sock_in, 0);
		    YYACCEPT; 
		 }
		 else {
		    DLDdbg << "--DLD_run = " << DLD_run << endl << flush;
		    DLDout << "ok;" << endl << flush;
		 }
	      } 
            ;

dialogscript: globalvars DLD_ENV_END { DLD_lineno = 0; } ';'
              globalvars maindialog mainempty
            ;

mainempty: /* empty */
         | maindialog;

globalvars:  /* empty */ 
           | globalvars VARIABLE '=' value
             { DLD_GUI->set_env($2,$4);} ';'
           | globalvars ';'
           ;

/* dialog "Dialogtitle" { commands...} */
maindialog:  DIALOG name 
             {  
		obj = container = dialog 
		   = DLD_GUI->dialog($2, DLD_Out(DLD_Outpath)); 
             } 
             sizeempty
             '{' { container->open_brace();}
                blockempty 
             '}' { container->close_brace(); }
            | name 
             {  
		obj = container = dialog 
		   = DLD_GUI->dialog($1, DLD_Out(DLD_Outpath)); 
             } 
             sizeempty
             '{' { container->open_brace();}
                blockempty 
             '}' { container->close_brace(); }
            ;

blockempty: /* empty */
          | blockempty block
          ;

block  : 
       /* common commands */
         common ';' 

       /* common container block */
       | {cont_stack.push(container);} blockargs 
         '{'  {container->open_brace();}
           blockempty
         '}' {container->close_brace(); container = cont_stack.top(); cont_stack.pop();}

       /* special container blocks */
       | CHECKLIST name { obj = checklist  = container->checklist($2);} 
         varargs 
         '{' {checklist->open_brace();}
           checkblock 
         '}' {checklist->close_brace();}

       | RADIOLIST name { obj = radiolist  = container->radiolist($2);} 
         varargs 
         '{' {radiolist->open_brace();}
           radioblock 
         '}' {radiolist->close_brace(); }

       | LIST      name { obj = listwidget = container->list($2);} 
         listargs 
         '{' {listwidget->open_brace();}
           listblock 
         '}' {listwidget->close_brace(); }

       | COMBOBOX name  { obj = combobox   = container->combobox($2);}
         varargs 
         '{' { combobox->open_brace(); }
           comboblock 
         '}' { combobox->close_brace(); }

	 /* error handling 
       | error ';' { yyerrok; yyerror("TEST");} 
       | error ';' '}' {container->close_brace(); yyerrok; } block
       | error '}' {container->close_brace(); yyerrok; } block
*/
       ;

sizeargs: WIDTH NUMBER { if(obj)obj->widthP(atoi($2.c_str())); }
        | HEIGHT NUMBER { if(obj)obj->heightP(atoi($2.c_str())); }
        | fontargs
        ;

sizeempty: /* empty */
             | sizeempty sizeargs
             ;

blockargs:  /* empty */
            | FORM   name {obj = container = container->form($2);}   sizeempty
            | ROW    name {obj = container = container->row($2);}    sizeempty
            | COL    name {obj = container = container->col($2);}    sizeempty
            | DIALOG name {obj = container = container->dialog($2);} sizeempty
            ;

listargs: varargs MULTI { listwidget->set_multi(true);} varargs
        | varargs
        ;

listblock: /* empty */
         | listblock LISTITEM constring { obj = listwidget->listitem($3);} 
            args ';' 
          ;

comboblock: /* empty */
          | comboblock COMBOITEM constring { obj = combobox->comboitem($3);}
            args ';' 
          ;

checkblock: /* empty */
          | checkblock CHECKBUTTON constring 
            { obj = checklist->checkbutton($3);} args ';' 
          ;

radioblock: /* empty */
          | radioblock RADIOBUTTON constring { obj = radiolist->radiobutton($3);} 
            args ';' 
          ;

common: /* empty */
       | BUTTON constring 
         { obj = button = container->button($2);} buttonargs
       | TEXT   constring { obj = container->text($2);  } sizeempty
       | IMAGE  constring { obj = container->image($2);  } sizeempty
       | MOVIE  constring { obj = image = container->image($2);
                            if(image)image->setIsMovie(true); } sizeempty
       | TEXTBOX  name 
         { obj = textbox = container->textbox($2);} textboxargs
       | MENUITEM  constring 
         { obj = menu = container->menu($2,0);} menuargs 
       | MENUCHECK constring 
         { obj = menu = container->menu($2,1);} menucheckargs
       | GAUGE name { obj = container->gauge($2); } gaugeargs
       | INPUT name { obj = input = container->input($2); } inputargs 
       | VARIABLE '=' value {DLD_GUI->set_env($1,$3);}
       ;

buttonargs: args SIGN { button->set_signature(true); } args
          | args
          ;

textboxargs: /* empty */
           | textboxargs FILEARG constring { textbox->set_filename($3);}
           | textboxargs sizeargs
	   ;

menuargs: /* empty */ 
         | menuargs EXEC constring    { menu->add_exec($3);}
         | menuargs EXIT              { menu->set_exit(true);}
         | menuargs GLOBAL            { menu->set_global(true);}
         ;

menucheckargs: /*empty */
         | menucheckargs varsetaddargs
         | menucheckargs GLOBAL { menu->set_global(true);}
	 ;

gaugeargs: /* empty */
	 | gaugeargs VAR VARNAME { if(obj)obj->add_setvar($3, "");}
         | gaugeargs EXEC constring { if(obj)obj->add_exec($3);}
         | gaugeargs FORK           { if(obj)obj->set_killchild(false);}
         | gaugeargs EXIT           { if(obj)obj->set_exit(true);}
         | gaugeargs DISABLE { if(obj)obj->disable(); }
         | gaugeargs sizeargs
	 ;

inputargs: /* empty */
         | inputargs VAR VARNAME { input->add_setvar($3, "");}
         | inputargs PASSWD { input->set_passwd(true);}
         | inputargs IP { input->set_ip(true);}
         | inputargs NUMERIC { input->set_numeric(true);}
         | inputargs LENGTH NUMBER { input->set_length(atoi($3.c_str()));}
         | inputargs sizeargs
	 | inputargs DISABLE { if(obj)obj->disable(); }
         | inputargs EXIT           { obj->set_exit(true);}
	 ;

varargs: /* empty */
    | varargs VAR VARNAME { if(obj)obj->add_setvar($3, "");}
    | varargs EXEC constring        { if(obj)obj->add_exec($3);}
    | varargs DISABLE { if(obj)obj->disable(); }
    | varargs FORK                  { if(obj)obj->set_killchild(false);}
    | varargs EXIT                  { if(obj)obj->set_exit(true);}
    | varargs sizeargs
    ;

varsetaddargs:
      VAR VARNAME SET value { if(obj)obj->add_setvar($2, $4);}
    | VAR VARNAME ADD value { if(obj)obj->add_addvar($2, $4);}
    ;
	 
args: /* empty */
    | args varsetaddargs
    | args EXEC constring        { if(obj)obj->add_exec($3);}
    | args DISABLE { if(obj)obj->disable(); }
    | args FORK                  { if(obj)obj->set_killchild(false);}
    | args EXIT                  { if(obj)obj->set_exit(true);}
    | args IMAGEFILE constring { if(obj)obj->add_image($3);}
    | args MOVIEFILE constring { if(obj)obj->add_movie($3);}
    | args sizeargs
    | args error { yyerror("maybe missing ';'"); }
    ;

value: constring
     | VARNAME   {$$=$1;}
     | NUMBER    {$$=$1;}
     ;

name: /* empty */ {$$.erase();}
    | NAME {$$=$1;} name { $$= $$ + $3; }
    ;

fontargs: 
      FONT VARNAME colourargs { if(obj)obj->set_font($2, "normal");}
    | FONT VARNAME colourargs SIZE value colourargs { if(obj)obj->set_font($2, $5);}
    ;

colourargs: /* empty */
    | colourargs BG value { if(obj)obj->set_bg($3);}
    | colourargs FG value { if(obj)obj->set_fg($3);}
    ;

constring: NAME {$$=$1;} name {$$ = $$ + $3; }
         ;

%%
int DLD_error = 0;

int yyerror(char *s)
{ 
  int i;

  DLDerr.form("stdin:%ld:%sstdin:%ld:", DLD_lineno, DLD_line, DLD_lineno);
  for ( i = 0; i < (DLD_linepos-yyleng); i++ ) {
    if(isspace(DLD_line[i]))
      DLDerr << DLD_line[i];
    
      DLDerr << ' ';
  }

  DLDerr << "^ " << s << endl  << flush;  
  DLD_error = 1;

  if (DLD_GUI)
     DLD_GUI->print_status ("Error parsing input! ...");

  if(DLD_Outpath.length()) {
     ofstream out(DLD_Outpath.c_str());
     out << "error;" << endl << flush;
     out.close();
#ifdef DEBUG
     DLDdbg << "error; --> client" << endl << flush;
#endif
     DLD_Outpath.erase();
  }
  return 0;
}

int
dld_parse ()
{

   if (DLD_GUI)
      DLD_GUI->print_status ("Parsing input ...");
   do
   {
      DLD_GUI->exec();
   } while(DLD_run > 0 && (!DLD_error));

   return DLD_error;
}

/******************************************************************************
**
** $Id: dld_obj.cc,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include <unistd.h>

#include "dld_obj.h"
#include "dld_dialog.h"
#include "dld_parser.h"
#include "dldialog.h"
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define inline
extern char **environ;

DLD_Obj::~DLD_Obj()
{
   for(CI i = childlist.begin(); i != childlist.end(); i = childlist.begin()) {
      delete *i;
   }
   
   if(execpid) {
      int status;
      int exitstatus=0;
      pid_t pid = waitpid(execpid, &status, WNOHANG);
      if( pid != 0 )
      {
	 if(pid > 0 && WIFEXITED(status)) {
	    exitstatus = WEXITSTATUS(status);
	    DLDdbg << execstr << " exited with " << exitstatus << endl << flush;
	 }
	 else if (pid > 0 && WIFSIGNALED(status)) {
	    exitstatus = WTERMSIG(status);
	    DLDdbg << execstr << " killed with signal " << exitstatus << endl << flush;
	 }
/*
	 execpid = 0;      
	 DLD_run--;
	 DLDdbg << "--DLD_run = " << DLD_run << endl << flush;
*/
      } else {
	 if(killchilds)
            kill(execpid, SIGTERM);
      }
   }

   if(parent_obj)
      parent_obj->del_child(this);
}

void DLD_Obj::create()
{ 
#ifdef DEBUG
   DLDdbg << "created object\n";
#endif
   is_created = true; 
}

inline void DLD_Obj::
add_setvar (const string& name, const string val) 
{
   varname = name; 
   varvalue = val; 
   varaddflag = false;
   dialog->register_var(name);
}

inline void DLD_Obj::set_font(const string& fname, const string& fsize )
{
   if (fsize == "mini") fontsize = 8; 
   else if (fsize == "small") fontsize = 10;
   else if (fsize == "normal") fontsize = 12;
   else if (fsize == "large") fontsize = 14;
   else if (fsize == "huge") fontsize = 16;
   else if (fsize == "big") fontsize = 18;
   else if ((fontsize = atoi(fsize.c_str())) != 0);   
   else fontsize = 12;
   fontname = fname;
}

inline void DLD_Obj::set_fg (const string &fg ) 
{
  fg_color = fg;
}

inline void DLD_Obj::set_bg (const string &bg ) 
{
  bg_color = bg;
}


inline void DLD_Obj::
add_addvar (const string& name, const string val)
{
   varname = name;
   varvalue = val; 
   varaddflag = true;
   dialog->register_var(name);
}

inline void DLD_Obj::
activate()
{   
#ifdef DEBUG
      DLDdbg << "gen_obj  activate " << endl << flush;
#endif
   if(varname.length()) {

      if(oldvalue.length() == 0)
	 oldvalue = dialog->get_env(varname);

      if(varaddflag) {
	 string newval = dialog->get_env(varname) + " " + varvalue;
	 dialog->set_env(varname, newval, this);
      }
      else
	 dialog->set_env(varname, varvalue, this);
   }

   if(execstr.length()) {
#ifdef DEBUG
      DLDdbg << "gen_obj  exec " << execstr << endl << flush;
#endif
      int pid;
      
      if ((pid = fork ()) == 0) {
	 char *argv[4];
	 int i;

	 dialog->set_up_environment();

	 dup2 (tty_fdin, STDIN_FILENO);
	 dup2 (tty_fdout, STDOUT_FILENO);
	 dup2 (fd_err, STDERR_FILENO);

	 for (i = 4; i < 256; i++)
	    close (i);

	 char exec[execstr.length()+1];
	 strcpy (exec, execstr.c_str());

	 exit(system(exec));
      }
/*      DLD_run++;      
      DLDdbg << "++DLD_run = " << DLD_run << endl << flush;
*/
      execpid = pid;
   }
}

inline void DLD_Obj::
deactivate()
{
   if(varname.length()) {
      if (varaddflag)
	 dialog->set_env(varname, oldvalue, this);
      else
	 dialog->del_env(varname, this);
   }
}

inline bool DLD_Obj::test_env (const string& _value)
{
   Assert(Bad_arg, dialog);
#ifdef DEBUG
   DLDdbg << "checking " << varname << " == " << _value << " varaddflag = " << varaddflag << endl << flush;
#endif   
   return dialog->test_env(varname, _value, varaddflag);
}

inline bool DLD_Obj::test_env ()
{
   Assert(Bad_arg, dialog);
   return dialog->test_env(varname, varvalue, varaddflag);
}

void DLD_Obj::add_child(DLD_Obj *obj)
{
   Assert(Bad_arg, obj != NULL);
   
   childlist.push_back(obj);
   obj->parent_obj = this;
}

void DLD_Obj::del_child(DLD_Obj *obj)
{
   Assert(Bad_arg, obj != 0);

   for(CI i = childlist.begin(); i != childlist.end(); ++i) {
      DLD_Obj *childptr = *i;
      if (childptr == obj) {
	 childlist.erase(i);
	 break;
      }
   }
}

string convstr (const string& _str)
{
   const char *str = _str.c_str();
   char *nstr = new char[_str.length() + 1];

   int p = 0;
   int q = 0;
   char c, count;

   while ((c = str[p++]) != '\0') {
      if (c == '\\') {
	 switch (str[p++]) {
	 case 'a':
	    c = '\a';
	    break;
	 case 'b':
	    c = '\b';
	    break;
	 case 'f':
	    c = '\f';
	    break;
	 case 'n':
	    c = '\n';
	    break;
	 case 'r':
	    c = '\r';
	    break;
	 case 't':
	    c = '\t';
	    break;
	 case 'v':
	    c = '\v';
	    break;
	 case '\\':
	    break;		/*
				 * * * * c = '\\' 
				 */
	 case '0':
	    c = 0;
	    for (count = 3; (count > 0) && ((unsigned) (str[p] - '0') < 8); count--);
	    c = (c << 3) + (str[p++] - '0');
	    break;
	 default:
//      c = str[p-1];
	    p--;
	    continue;
	    break;
	 }
      }
      nstr[q++] = c;
   }

   nstr[q] = '\0';

   string ret(nstr);
   delete nstr;
   return ret;
}

#undef inline

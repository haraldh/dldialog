%{/*-*- C++ -*-*/
/******************************************************************************
**
** $Id: dld_parser_lex.ll,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
**
** The Lex File for DLDialog
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
**
******************************************************************************/
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <libintl.h>
#include "dldialog.h"
#include "dld_lib.h"
#include "dld_parser.h"
#include "dld_parser_yacc.h"

#undef YY_BUF_SIZE
#define YY_BUF_SIZE (YYLMAX-1)

#undef YY_READ_BUF_SIZE
#define YY_READ_BUF_SIZE (YYLMAX-1)

#ifndef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( yy_current_buffer->yy_is_interactive ) \
		{ \
		int c = '*', n; \
		for ( n = 0; n < max_size && \
			     (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
			buf[n] = (char) c; \
		if ( c == '\n' ) \
			buf[n++] = (char) c; \
		if ( c == EOF && ferror( yyin ) ) \
			YY_FATAL_ERROR( "input in flex scanner failed" ); \
		result = n; \
		} \
	else { \
                buf[0]=0; \
                if ( (( fgets( buf, max_size, yyin )) == 0) \
		  && ferror( yyin ) && (errno != EAGAIN) ) \
		YY_FATAL_ERROR( "input in flex scanner failed" ); \
             } \
   result = strlen(buf); \
   strncpy(DLD_line, buf, YY_READ_BUF_SIZE); \
   DLD_linepos=0; \
   DLD_lineno++; \
   DLD_line[YY_READ_BUF_SIZE]=0; 
#endif

%}

%start COMMAND ARGS

letter [a-zA-z]
alpha [0-9]
special [_-]
varname {letter}({letter}|{alpha}|{special})*
number {alpha}+
sep [ \t\n\;\{\}]

%%

%{
/* Commands for dldialog */
%}
<COMMAND>"dld_env_end"/{sep} { DLD_linepos+=yyleng; return (DLD_ENV_END);}
<COMMAND>"dialog"/{sep}      { DLD_linepos+=yyleng; BEGIN ARGS; return(DIALOG);}

<COMMAND>"form"/{sep}        { DLD_linepos+=yyleng; BEGIN ARGS; return(FORM);} 
<COMMAND>"row"/{sep}         { DLD_linepos+=yyleng; BEGIN ARGS; return(ROW);} 
<COMMAND>"col"/{sep}         { DLD_linepos+=yyleng; BEGIN ARGS; return(COL);} 

<COMMAND>"checklist"/{sep}   { DLD_linepos+=yyleng; BEGIN ARGS; return(CHECKLIST);}
<COMMAND>"checkbutton"/{sep} { DLD_linepos+=yyleng; BEGIN ARGS; return(CHECKBUTTON);}

<COMMAND>"radiolist"/{sep}   { DLD_linepos+=yyleng; BEGIN ARGS; return(RADIOLIST);}
<COMMAND>"radiobutton"/{sep} { DLD_linepos+=yyleng; BEGIN ARGS; return(RADIOBUTTON);}

<COMMAND>"list"/{sep}        { DLD_linepos+=yyleng; BEGIN ARGS; return(LIST);}
<COMMAND>"listitem"/{sep}    { DLD_linepos+=yyleng; BEGIN ARGS; return(LISTITEM);}

<COMMAND>"combobox"/{sep}    { DLD_linepos+=yyleng; BEGIN ARGS; return(COMBOBOX);} 
<COMMAND>"comboitem"/{sep}   { DLD_linepos+=yyleng; BEGIN ARGS; return(COMBOITEM);}

<COMMAND>"menuitem"/{sep}    { DLD_linepos+=yyleng; BEGIN ARGS; return(MENUITEM);}
<COMMAND>"menucheck"/{sep}   { DLD_linepos+=yyleng; BEGIN ARGS; return(MENUCHECK);}

<COMMAND>"text"/{sep}        { DLD_linepos+=yyleng; BEGIN ARGS; return(TEXT);}
<COMMAND>"button"/{sep}      { DLD_linepos+=yyleng; BEGIN ARGS; return(BUTTON);}
<COMMAND>"gauge"/{sep}       { DLD_linepos+=yyleng; BEGIN ARGS; return(GAUGE);}
<COMMAND>"input"/{sep}       { DLD_linepos+=yyleng; BEGIN ARGS; return(INPUT);}

<COMMAND>"textbox"/{sep}     { DLD_linepos+=yyleng; BEGIN ARGS; return(TEXTBOX);}
<COMMAND>"image"/{sep}       { DLD_linepos+=yyleng; BEGIN ARGS; return(IMAGE);}
<COMMAND>"movie"/{sep}       { DLD_linepos+=yyleng; BEGIN ARGS; return(MOVIE);}

<COMMAND>{varname}/[ \t]*=         { 
   DLD_linepos+=yyleng; 
   yylval.dld_string=yytext; 
   return(VARIABLE); 
}

%{
/* Arguments for the commands */
%}
<ARGS>"\-var"/{sep}           { DLD_linepos+=yyleng; return(VAR); }
<ARGS>"\-set"/{sep}           { DLD_linepos+=yyleng; return(SET); }
<ARGS>"\-add"/{sep}           { DLD_linepos+=yyleng; return(ADD); }
<ARGS>"\-exec"/{sep}          { DLD_linepos+=yyleng; return(EXEC); }
<ARGS>"\-fork"/{sep}          { DLD_linepos+=yyleng; return(FORK); }
<ARGS>"\-multi"/{sep}         { DLD_linepos+=yyleng; return(MULTI); }
<ARGS>"\-exit"/{sep}          { DLD_linepos+=yyleng; return(EXIT); }
<ARGS>"\-global"/{sep}        { DLD_linepos+=yyleng; return(GLOBAL); }
<ARGS>"\-numeric"/{sep}       { DLD_linepos+=yyleng; return(NUMERIC); }
<ARGS>"\-ip"/{sep}            { DLD_linepos+=yyleng; return(IP); }
<ARGS>"\-passwd"/{sep}        { DLD_linepos+=yyleng; return(PASSWD); }
<ARGS>"\-length"/{sep}        { DLD_linepos+=yyleng; return(LENGTH); }
<ARGS>"\-width"/{sep}         { DLD_linepos+=yyleng; return(WIDTH); }
<ARGS>"\-height"/{sep}        { DLD_linepos+=yyleng; return(HEIGHT); }
<ARGS>"\-file"/{sep}          { DLD_linepos+=yyleng; return(FILEARG); }
<ARGS>"\-image"/{sep}         { DLD_linepos+=yyleng; return(IMAGEFILE); }
<ARGS>"\-movie"/{sep}         { DLD_linepos+=yyleng; return(MOVIEFILE); }
<ARGS>"\-sign"/{sep}          { DLD_linepos+=yyleng; return(SIGN); }
<ARGS>"\-font"/{sep}          { DLD_linepos+=yyleng; return(FONT); }
<ARGS>"\-size"/{sep}          { DLD_linepos+=yyleng; return(SIZE); }
<ARGS>"\-bg"/{sep}            { DLD_linepos+=yyleng; return(BG); }
<ARGS>"\-fg"/{sep}            { DLD_linepos+=yyleng; return(FG); }
<ARGS>"\-disable"/{sep}       { DLD_linepos+=yyleng; return(DISABLE); }

%{
/* Overread everything that is quoted with a backslash */
%}
\"([^\\\"]*(\\.)?)*\" { DLD_linepos+=yyleng; 
                              yytext[yyleng-1]=0; 
			      if (strlen(&yytext[1])) {
				 textdomain (PACKAGE"-scripts");
				 yylval.dld_string = gettext(&yytext[1]);
				 textdomain (PACKAGE);
			      }
			      else
				 yylval.dld_string = &yytext[1];
			      return(NAME); }

\'([^\\\']*(\\.)?)*\' { DLD_linepos+=yyleng; 
                              yytext[yyleng-1]=0; 
			      if (strlen(&yytext[1])) {
				 textdomain (PACKAGE"-scripts");
				 yylval.dld_string = gettext(&yytext[1]);
				 textdomain (PACKAGE);
			      }
			      else
				 yylval.dld_string = &yytext[1];
			      return(NAME); 
}

<ARGS>{number}/{sep}          { DLD_linepos+=yyleng; 
                                yylval.dld_string = yytext; 
                                return(NUMBER); }

<ARGS>{varname}/{sep}         { DLD_linepos+=yyleng; 
                                yylval.dld_string = yytext; 
                                return(VARNAME); }

%{
/* client - server communication */
%}
"dld_start"/{sep}  { DLD_linepos+=yyleng; return (DLD_START);}
"dld_stop"/{sep}   { DLD_linepos+=yyleng; return (DLD_STOP);}
"dld_client"/{sep} { DLD_linepos+=yyleng; BEGIN COMMAND; return (DLD_CLIENT);}


%{
/* comments and spaces */
%}

\#[^\n]*[\n]                { DLD_linepos+=yyleng; }
\/\/[^\n]*[\n]              { DLD_linepos+=yyleng; }
[ \t]+                      { DLD_linepos+=yyleng; }
\n                          { DLD_linepos+=yyleng; }

%{
/* delimeters */
%}

\;                          { DLD_linepos+=yyleng; 
                              BEGIN COMMAND; return(';'); }
\=                          { DLD_linepos+=yyleng; 
                              BEGIN ARGS; return('='); }
\{                          { DLD_linepos+=yyleng; 
                              BEGIN COMMAND; return('{'); }
\}                          { DLD_linepos+=yyleng; 
                              BEGIN COMMAND; return('}'); }

.                           { DLD_linepos+=yyleng; return yytext[0]; }

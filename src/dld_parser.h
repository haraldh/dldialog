/**-*- C++ -*-*****************************************************************
**
** $Id: dld_parser.h,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
**
**	This program is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License
**	as published by the Free Software Foundation; either version
**	2 of the License, or (at your option) any later version.
**
** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
**
******************************************************************************/

#ifndef DLD_PARSER_H
#define DLD_PARSER_H

#include <string>

#undef YYLMAX
#define YYLMAX (1024*32) 

/// store actually read line hier
extern char     DLD_line[YYLMAX];

/// linenumber and position
extern long     DLD_lineno, DLD_linepos;

/// length of line
extern int      yyleng;

/// parse function
int             yyparse (void);

extern int DLD_run;

#ifdef __cplusplus
extern          "C" {
#endif

/*
 * C definitions  
 */
#include <stdio.h>
   /// lexical analysis
   int             yylex (void);

   /// file id for input
   extern FILE    *yyin;

   /// function to call on a parsing error
   int             yyerror (char *s);


#ifdef __cplusplus
}
// C++ declarations

#include <iostream.h>
#include <exception>

/// global dldialog parse function
int dld_parse ();

/// Internal error variable
extern int DLD_error;

/**
 * Parse error exception.
 * @short Parse error exception.
 * @author Harald Hoyer <HarryH@Royal.Net>
 */
class DLD_Parse_Error : public exception {   
};

/**
 * Pipe error exception.
 * @short Pipe error exception.
 * @author Harald Hoyer <HarryH@Royal.Net>
 */
class DLD_Pipe_Error : public exception {   
};

struct YYSTYPE {
   string dld_string;
};

#endif

#endif

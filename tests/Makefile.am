#/*****************************************************************************
#**
#** $Id: Makefile.am,v 1.2 2002/04/04 15:25:25 saturn_de Exp $
#**
#**	This program is free software; you can redistribute it and/or
#**	modify it under the terms of the GNU General Public License
#**	as published by the Free Software Foundation; either version
#**	2 of the License, or (at your option) any later version.
#**
#** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
#**
#*****************************************************************************/

TESTS = ${srcdir}/test1 ${srcdir}/test2 ${srcdir}/test8 ${srcdir}/test6
EXTRA_DIST = test1 test1.cmp test2 test2.cmp test3 test4 \
             test5 test6 test7 test8 test9 \
	     example1 example2 example3 example4 dldialog_funcs \
	     extractstr.awk dldialog-scripts.po \
	     pnglogo.png DLD.xpm DLD-start.xpm calc

localedir = $(datadir)/locale

po_DATA = dldialog-scripts.mo

podir = $(localedir)/de/LC_MESSAGES

dldialog-scripts.mo: ${srcdir}/dldialog-scripts.po
	msgfmt -o $@ $<

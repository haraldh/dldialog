#/*****************************************************************************
#**
#** $Id: Makefile.am,v 1.3 2002/04/04 15:25:24 saturn_de Exp $
#**
#**	This program is free software; you can redistribute it and/or
#**	modify it under the terms of the GNU General Public License
#**	as published by the Free Software Foundation; either version
#**	2 of the License, or (at your option) any later version.
#**
#** by Harald Hoyer (dldialog@parzelle.de) 
#** Copyright (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
#**
#*****************************************************************************/
SUBDIRS = qt tv

EXTRA_DIST = base.kdoc $(wildcard *.html)  

if CLASSDOC
base_DATA =  base.kdoc $(wildcard *.html)
basedir = $(prefix)/doc/dldialog-@VERSION@/classdoc

KDOC = @KDOC@

base.kdoc:  $(wildcard $(top_srcdir)/src/*.h)
	@(cd $(top_srcdir)/src/; \
	if [ -n "$(KDOC)" ]; then \
		$(KDOC) -f html -L ../doc/classdoc -n base -u ../ -d ../doc/classdoc *.h; \
	else \
		touch ../doc/classdoc/base.kdoc; \
	fi)
endif

clean:
	rm -f base.kdoc ./*.html 

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
EXTRA_DIST = dld_qt.kdoc $(wildcard *.html)

if CLASSDOC
qt_DATA = dld_qt.kdoc $(wildcard *.html) 
qtdir = $(prefix)/doc/dldialog-@VERSION@/classdoc/qt
PWD = $(shell pwd)

dld_qt.kdoc: $(srcdir)/../base.kdoc $(wildcard $(top_srcdir)/src/DLD_QT/*.h)
	(cd $(top_srcdir)/src/; \
	if [ -n "$(KDOC)" ]; then \
		$(KDOC) -n dld_qt -f html -L ../doc/classdoc/ -l base \
			--liboutdir ../doc/classdoc/qt \
			-d ../doc/classdoc/qt  \
			DLD_QT/*.h ; \
	else \
		touch ../doc/classdoc/qt/qt.kdoc; \
	fi)

$(srcdir)/../base.kdoc:
	make -C $(srcdir)/.. base.kdoc

endif

clean:
	rm -f qt.kdoc ./*.html 

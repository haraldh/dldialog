#/*****************************************************************************
#**
#** $Id: Makefile.am,v 1.1 2001/03/14 02:32:31 saturn_de Exp $
#**
#**	This program is free software; you can redistribute it and/or
#**	modify it under the terms of the GNU General Public License
#**	as published by the Free Software Foundation; either version
#**	2 of the License, or (at your option) any later version.
#**
#** by Harald Hoyer (HarryH@Royal.Net) 
#** for delix Computer GmbH (http://www.delix.de)
#**
#*****************************************************************************/
EXTRA_DIST = qt.kdoc $(wildcard *.html)

if CLASSDOC
qt_DATA = qt.kdoc $(wildcard *.html) 
qtdir = $(prefix)/doc/dldialog-@VERSION@/classdoc/qt

qt.kdoc: $(srcdir)/../base.kdoc $(wildcard $(top_srcdir)/src/DLD_QT/*.h)
	@(cd $(top_srcdir)/src/; \
	if [ -n "$(KDOC)" ]; then \
		$(KDOC) ../doc/classdoc/qt/qt -d../doc/classdoc/qt  \
			DLD_QT/*.h -l../doc/classdoc/base; \
	else \
		touch ../doc/classdoc/qt/qt.kdoc; \
	fi)

$(srcdir)/../base.kdoc:
	make -C $(srcdir)/.. base.kdoc

endif

clean:
	rm -f qt.kdoc ./*.html 

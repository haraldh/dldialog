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

EXTRA_DIST = dld_tv.kdoc $(wildcard *.html)

if CLASSDOC
tv_DATA = dld_tv.kdoc $(wildcard *.html) 
tvdir = $(prefix)/doc/dldialog-@VERSION@/classdoc/tv

dld_tv.kdoc: $(srcdir)/../base.kdoc $(wildcard $(top_srcdir)/src/DLD_TV/*.h)
	(cd $(top_srcdir)/src/; \
	if [ -n "$(KDOC)" ]; then \
		$(KDOC) -n dld_tv -f html -L ../doc/classdoc/ -l base \
			--liboutdir ../doc/classdoc/tv \
			-d ../doc/classdoc/tv  \
			DLD_TV/*.h ; \
	else \
		touch ../doc/classdoc/tv/tv.kdoc; \
	fi)

$(srcdir)/../base.kdoc:
	make -C $(srcdir)/.. base.kdoc

endif

clean:
	rm -f tv.kdoc ./*.html 

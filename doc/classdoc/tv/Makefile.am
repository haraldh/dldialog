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

EXTRA_DIST = tv.kdoc $(wildcard *.html)

if CLASSDOC
tv_DATA = tv.kdoc $(wildcard *.html) 
tvdir = $(prefix)/doc/dldialog-@VERSION@/classdoc/tv

tv.kdoc: $(srcdir)/../base.kdoc $(wildcard $(top_srcdir)/src/DLD_TV/*.h)
	@(cd $(top_srcdir)/src/; \
	if [ -n "$(KDOC)" ]; then \
		$(KDOC) ../doc/classdoc/tv/tv -d../doc/classdoc/tv  \
			DLD_TV/*.h -l../doc/classdoc/base; \
	else \
		touch ../doc/classdoc/tv/tv.kdoc; \
	fi)

$(srcdir)/../base.kdoc:
	make -C $(srcdir)/.. base.kdoc

endif

clean:
	rm -f tv.kdoc ./*.html 

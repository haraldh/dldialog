#/***********************************************************************
#**
#** $Id: Makefile.am,v 1.4 2002/04/04 15:42:31 saturn_de Exp $
#**
#**	This program is free software; you can redistribute it and/or
#**	modify it under the terms of the GNU General Public License
#**	as published by the Free Software Foundation; either version
#**	2 of the License, or (at your option) any later version.
#**
#** (C) 1998-2002 Harald Hoyer <DLDialog@parzelle.de> - All rights reserved -
#**
#***********************************************************************/
AUTOMAKE_OPTIONS = gnu 

dnl SUBDIRS =  intl src po perl tests 
SUBDIRS = m4 intl doc src po perl tests 

EXTRA_DIST = config.rpath  README.developer dldialog.spec README.QT autogen.sh ChangeLog.old

docdir = $(prefix)/doc/dldialog-@VERSION@

doc_DATA = AUTHORS COPYING ChangeLog INSTALL TODO NEWS README README.QT 

.PHONY: rp3 changelog srpm

changelog:
	rcs2log | sed -e 's|/cvsroot/dldialog/dldialog/||g' \
		-e 's|@.*\.redhat\.com|@redhat.com|g' -e 's|saturn_de|harald|g' > ChangeLog
	cat $(srcdir)/ChangeLog.old >>ChangeLog

dist: configure Makefile config.h changelog

srpm: distcheck rp3-1.1.10.tar.gz
	rpmbuild --define "_sourcedir `pwd`" --define "_srcrpmdir `pwd`" --define "_specdir `pwd`" -ts @PACKAGE@-@VERSION@.tar.gz




#/***********************************************************************
#**
#** $Id: Makefile.am,v 1.2 2002/04/04 12:49:20 saturn_de Exp $
#**
#**	This program is free software; you can redistribute it and/or
#**	modify it under the terms of the GNU General Public License
#**	as published by the Free Software Foundation; either version
#**	2 of the License, or (at your option) any later version.
#**
#** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de> 
#**
#***********************************************************************/
AUTOMAKE_OPTIONS = gnu 

dnl SUBDIRS =  intl src po perl tests 
SUBDIRS =  intl doc src po perl tests 

EXTRA_DIST = README.developer dldialog.spec README.QT autogen.sh

docdir = $(prefix)/doc/dldialog-@VERSION@

doc_DATA = AUTHORS COPYING ChangeLog INSTALL TODO NEWS README README.QT 

.PHONY: rp3 changelog srpm

changelog:
	rcs2log | sed -e 's|/cvsroot/dldialog/dldialog/||g' \
		-e 's|@.*\.redhat\.com|@redhat.com|g' -e 's|saturn_de|harald|g' > ChangeLog
	cat ChangeLog.old >>ChangeLog

dist: configure Makefile config.h changelog

srpm: distcheck rp3-1.1.10.tar.gz
	rpmbuild --define "_sourcedir `pwd`" --define "_srcrpmdir `pwd`" --define "_specdir `pwd`" -ts @PACKAGE@-@VERSION@.tar.gz

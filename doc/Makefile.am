#/*****************************************************************************
#**
#** $Id: Makefile.am,v 1.2 2002/04/04 15:25:24 saturn_de Exp $
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

SUBDIRS = classdoc

EXTRA_DIST = dldialog.sgml.cpp index.html top.html frame.html qt.gif red.gif \
             tv.gif dldialog.1 dldialog.sgml.cpp $(wildcard dldialog*.html) \
	     $(wildcard dldialog.info*) dldialog.txt dldialog.dvi dldialog.sgml	\
	     dldialog.man.sgml dldialog.man.sgml.in dldialog.man.sgml.body pre.awk \
	     tv-maxi.gif qt-maxi.gif

man_MANS = dldialog.1 

info_DATA = $(wildcard dldialog.info*)
infodir = $(prefix)/info

doc_DATA = $(wildcard dldialog*.html) dldialog.html dldialog.txt \
           dldialog.dvi dldialog.sgml dldialog.man.sgml index.html top.html \
	frame.html qt.gif red.gif tv.gif tv-maxi.gif qt-maxi.gif

docdir = $(prefix)/doc/dldialog-@VERSION@

${srcdir}/dldialog.sgml: ${srcdir}/dldialog.sgml.cpp ${top_srcdir}/AUTHORS \
	${top_srcdir}/TODO ${top_srcdir}/ChangeLog ${top_srcdir}/COPYING \
	${top_srcdir}/INSTALL ${top_srcdir}/NEWS \
	${srcdir}/dldialog.man.sgml.body ${top_srcdir}/configure.in
	gawk -f ${srcdir}/pre.awk $<|sed -e 's/\@VERSION\@/@VERSION@/g' \
	-e 's/\@DATE\@/$(shell date +"%x")/g' \
	  >$@	

dldialog.man.sgml: ${srcdir}/dldialog.man.sgml.in \
	${srcdir}/dldialog.man.sgml.body ${top_srcdir}/AUTHORS \
	${top_srcdir}/configure.in
	gawk -f ${srcdir}/pre.awk $<|sed -e 's/\@VERSION\@/@VERSION@/g' \
	-e 's/\@DATE\@/$(shell date +"%x")/g' \
	  >$@	

if SGMLTOOLS
dldialog.info: ${srcdir}/dldialog.sgml
	sgml2info ${srcdir}/dldialog.sgml

if HAVE_LATEX
dldialog.dvi: ${srcdir}/dldialog.sgml
	sgml2latex -p a4 -o dvi ${srcdir}/dldialog.sgml
endif

dldialog.txt: ${srcdir}/dldialog.sgml
	sgml2txt ${srcdir}/dldialog.sgml

dldialog.html: ${srcdir}/dldialog.sgml
	sgml2html ${srcdir}/dldialog.sgml

dldialog.1: ${srcdir}/dldialog.man.sgml
	sgml2txt -man ${srcdir}/dldialog.man.sgml && mv dldialog.man.man \
	    dldialog.1
endif

maintainer-clean:
	rm -f dldialog*.html dldialog.info dldialog.log \
	      dldialog.sgml *~ dldialog.1 dldialog.tex dldialog.toc \
	      dldialog.man \
	      dldialog.txt dldialog.aux dldialog.dvi dldialog.man.sgml

clean:
	rm -f dldialog.sgml dldialog.man.sgml *~

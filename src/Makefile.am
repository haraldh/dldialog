#/*****************************************************************************
#**
#** $Id: Makefile.am,v 1.1 2001/03/14 02:32:56 saturn_de Exp $
#**
#**	This program is free software; you can redistribute it and/or
#**	modify it under the terms of the GNU General Public License
#**	as published by the Free Software Foundation; either version
#**	2 of the License, or (at your option) any later version.
#**
#** (C) 1999,2000 Harald Hoyer <DLDialog@parzelle.de>
#**
#*****************************************************************************/

EXTRA_DIST = parser.sed

SUBDIRS = DLD_GEN DLD_TV DLD_QT 
dldialog_LDADD =  @INTLLIBS@ @LEXLIB@ -ldl
dldialog_LDFLAGS = -export-dynamic

bin_PROGRAMS = dldialog

dldialog_SOURCES = dldialog.cc dld_obj.cc dld_out.cc dld_gauge.cc dld_dialog.cc \
		dld_gui.cc dldialog.h dld_parser_yacc.yy dld_parser_lex.ll \
dld_button.h       dld_dialog.h       dld_list.h         dld_radiobutton.h \
dld_checkbutton.h  dld_form.h         dld_listitem.h     dld_radiolist.h \
dld_checklist.h    dld_gauge.h        dld_menu.h         dld_row.h \
dld_col.h          dld_gui.h          dld_obj.h          dld_text.h \
dld_combobox.h     dld_image.h        dld_out.h          dld_textbox.h \
dld_comboitem.h    dld_input.h        dld_parser.h \
dld_container.h    dld_lib.h          dld_parser_yacc.h 

# .yy.cc:

%.cc: %.yy
	$(YACC) $(AM_YFLAGS) $(YFLAGS) $< && sed -f parser.sed y.tab.c >$*.cc \
	&& rm -f y.tab.c
	if test -f y.tab.h; then \
	if cmp -s y.tab.h $*.h; then rm -f y.tab.h; else mv y.tab.h $*.h; fi; \
	else :; fi

dld_parser_yacc.h: dld_parser_yacc.cc

dld_parser_yacc.cc: dld_parser_yacc.yy parser.sed

YFLAGS = -d 

# INCLUDES = -DLIBDIR="\"@libdir@\"" 
localedir = $(datadir)/locale
# INCLUDES = -I $(top_srcdir)/intl -DLOCALEDIR=\"$(localedir)\"
INCLUDES = -DLOCALEDIR=\"$(localedir)\"
EXTRA_dldialog_SOURCES = dld_parser_yacc.h

all-recursive: dld_parser_yacc.h dld_parser_yacc.cc

# DLD_TV/libdld_tv.la: all-recursive
# DLD_QT/libdld_qt.la: all-recursive
# DLD_GEN/libdld_gen.la: all-recursive

#/*****************************************************************************
#**
#** $Id: Makefile.am,v 1.1 2001/03/14 02:33:07 saturn_de Exp $
#**
#**	This program is free software; you can redistribute it and/or
#**	modify it under the terms of the GNU General Public License
#**	as published by the Free Software Foundation; either version
#**	2 of the License, or (at your option) any later version.
#**
#**
#*****************************************************************************/

libdld_qt_la_LDFLAGS = -export-dynamic -version-info @GUI_VERSION_INFO@ @QT_LDFLAGS@ @X_LDFLAGS@
libdld_qt_la_LIBADD = @QT_LIBS@

INCLUDES = @QT_INCLUDES@

m%.cc: %.h
	@MOC@ $< -o $@

if BUILDQT
lib_LTLIBRARIES = libdld_qt.la
libdld_qt_la_SOURCES = dld_lib.cc dld_qtlib.h \
	dld_qtapp.cc dld_qtapp.h mdld_qtapp.cc \
	dld_qtcontainer.cc dld_qtcontainer.h \
	dld_dialog.cc dld_dialog.h mdld_dialog.cc \
	dld_text.cc dld_text.h \
	dld_button.cc dld_button.h  mdld_button.cc \
	dld_qtobj.cc dld_qtobj.h \
	dld_row.cc dld_row.h \
	dld_col.cc dld_col.h \
	dld_form.cc dld_form.h \
	dld_radio.cc dld_radio.h mdld_radio.cc \
	dld_radiolist.cc dld_radiolist.h mdld_radiolist.cc \
	dld_list.cc dld_list.h mdld_list.cc \
	dld_listitem.cc dld_listitem.h \
	dld_checklist.cc dld_checklist.h mdld_checklist.cc \
	dld_check.cc dld_check.h mdld_check.cc \
	dld_input.cc dld_input.h mdld_input.cc \
	dld_textbox.cc dld_textbox.h \
	dld_combobox.h dld_combobox.cc mdld_combobox.cc \
	dld_comboitem.h dld_comboitem.cc \
	dld_gauge.cc dld_gauge.h \
	dld_image.cc dld_image.h mdld_image.cc

clean-compile:
	rm -f m*.cc

endif


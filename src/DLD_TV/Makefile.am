#/*****************************************************************************
#**
#** $Id: Makefile.am,v 1.1 2001/03/14 02:33:13 saturn_de Exp $
#**
#**	This program is free software; you can redistribute it and/or
#**	modify it under the terms of the GNU General Public License
#**	as published by the Free Software Foundation; either version
#**	2 of the License, or (at your option) any later version.
#**
#**
#*****************************************************************************/
dnl AUTOMAKE_OPTIONS = foreign

libdld_tv_la_LDFLAGS = -export-dynamic -version-info @GUI_VERSION_INFO@ @TV_LDFLAGS@ 

libdld_tv_la_LIBADD = @TV_LIBS@

INCLUDES = @TV_INCLUDES@

if BUILDTV
lib_LTLIBRARIES = libdld_tv.la

libdld_tv_la_SOURCES =	\
	dld_lib.cc dld_tvlib.h \
	dld_tvapp.cc dld_tvapp.h \
	dld_tvobj.cc dld_tvobj.h \
	dld_geom.h dld_geom.cc \
	dld_tvcontainer.h dld_tvcontainer.cc \
	dld_dialog.h dld_dialog.cc \
	dld_form.cc dld_form.h \
	dld_row.cc dld_row.h \
	dld_col.cc dld_col.h \
	dld_checklist.cc dld_checklist.h \
	dld_radiolist.cc dld_radiolist.h \
	dld_tvcheck.cc dld_tvcheck.h \
	dld_tvradio.cc dld_tvradio.h \
	dld_button.h dld_button.cc \
	dld_text.cc dld_text.h \
	dld_list.cc dld_list.h \
	dld_listitem.cc dld_listitem.h \
	nmcmbobx.cpp  nmcmbown.cpp  tcmbovwr.cpp  tcombobx.cpp \
	nmcmbovw.cpp  nmsinput.cpp  tcmbowin.cpp  tsinputl.cpp \
	tcombobx.h tsinputl.h \
	dld_combobox.cc dld_combobox.h \
	dld_comboitem.cc dld_comboitem.h \
	dld_gauge.cc dld_gauge.h \
	fileview.cc fileview.h \
	dld_textbox.cc dld_textbox.h \
	dld_input.h dld_input.cc

#DEFS += -export-dynamic
endif

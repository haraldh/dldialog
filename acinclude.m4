## KDE/acinclude.m4 (Macros for autoconf)
##
## (C) 1997 Janos Farkas
## (C) 1997 Stephan Kulow

## ------------------------------------------------------------------------
## Find a file (or one of more files in a list of dirs)
## ------------------------------------------------------------------------
##
AC_DEFUN(AC_FIND_FILE,
[
$3=NO
for i in $2;
do
  for j in $1;
  do
    if test -r "$i/$j"; then
      $3=$i
      break 2
    fi
  done
done
])

## ------------------------------------------------------------------------
## Internal macros to find if we don't need extra flags to find these
## This is not yet used
## ------------------------------------------------------------------------
##
AC_DEFUN(AC_PATH_QT_DIRECT,
[if test "$ac_qt_includes" = NO; then
AC_TRY_CPP([#include <qtstream.h>],
[
ac_qt_includes=
],[
])
fi
])

## ------------------------------------------------------------------------
## Find the meta object compiler in the PATH, in $QTDIR/bin, and some
## more usual places
## ------------------------------------------------------------------------
##
AC_DEFUN(AC_PATH_QT_MOC,
[
AC_PATH_PROG(MOC, moc, /usr/bin/moc,
 $PATH:/usr/bin:/usr/X11R6/bin:$QTDIR/bin:/usr/lib/qt/bin:/usr/local/qt/bin)
])



## ------------------------------------------------------------------------
## Try to find the QT headers and libraries.
## $(QT_LDLFLAGS) will be -Lqtliblocation (if needed)
## and $(QT_INCLUDES) will be -Iqthdrlocation (if needed)
## ------------------------------------------------------------------------
##
AC_DEFUN(AC_PATH_QT_1_3,
[
AC_REQUIRE([AC_PATH_X])

AC_MSG_CHECKING([for QT-1.30])
ac_qt_includes=NO ac_qt_libraries=NO
qt_libraries=""
qt_includes=""
AC_ARG_WITH(qt-dir,
    [  --with-qt-dir           where the root of qt is installed ],
    [  ac_qt_includes="$withval"/include
       ac_qt_libraries="$withval"/lib
    ])

AC_ARG_WITH(qt-includes,
    [  --with-qt-includes      where the qt includes are. ],
    [  
       ac_qt_includes="$withval"
    ])
    
AC_ARG_WITH(qt-libraries,
    [  --with-qt-libraries     where the qt library is installed.],
    [  ac_qt_libraries="$withval"
    ])

if test "$ac_qt_includes" = NO || test "$ac_qt_libraries" = NO; then

AC_CACHE_VAL(ac_cv_have_qt,
AC_PATH_QT_DIRECT
[#try to guess qt locations

qt_incdirs="/usr/lib/qt/include /usr/local/qt/include /usr/include/qt /usr/include /usr/X11R6/include/X11/qt $x_includes $QTINC"
test -n "$QTDIR" && qt_incdirs="$QTDIR/include $QTDIR $qt_incdirs"
AC_FIND_FILE(qglobal.h, $qt_incdirs, qt_incdir)
ac_qt_includes=$qt_incdir

qt_libdirs="/usr/lib/qt/lib /usr/local/qt/lib /usr/lib/qt /usr/lib $x_libraries $QTLIB"
test -n "$QTDIR" && qt_libdirs="$QTDIR/lib $QTDIR $qt_libdirs"
AC_FIND_FILE(libqt.so libqt.so.1.30 libqt.so.1 libqt.a libqt.sl, $qt_libdirs, qt_libdir)
ac_qt_libraries=$qt_libdir

ac_cxxflags_safe=$CXXFLAGS
ac_ldflags_safe=$LDFLAGS
ac_libs_safe=$LIBS
CXXFLAGS="$CXXFLAGS -I$qt_incdir"
LDFLAGS="-L$qt_libdir $X_LDFLAGS"
LIBS="-lqt -lXext -lX11 $LIBSOCKET"
AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
#include <stdio.h>
#include <qglobal.h>
#if QT_VERSION < 130
#error QT_VERSION is too small
#else
main()
{
  puts(QT_VERSION_STR);
  return 0;
}
#endif
EOF

if AC_TRY_EVAL(ac_link) && test -s conftest; then
  rm -f conftest*
else
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.$ac_ext >&AC_FD_CC
  ac_qt_libraries="NO"
fi
rm -f conftest*
CXXFLAGS=$ac_cxxflags_safe
LDFLAGS=$ac_ldflags_safe
LIBS=$ac_libs_safe

if test "$ac_qt_includes" = NO || test "$ac_qt_libraries" = NO; then
  ac_cv_have_qt="have_qt=no"
  ac_qt_notfound=""
  if test "$ac_qt_includes" = NO; then
    if test "$ac_qt_libraries" = NO; then
      ac_qt_notfound="(headers and libraries)";
    else
      ac_qt_notfound="(headers)";
    fi
  else
    ac_qt_notfound="(libraries)";
  fi

  AC_MSG_ERROR([QT-1.30 $ac_qt_notfound not found. Please check your installation! ]);
else
  have_qt="yes"  
fi
])
else
  have_qt="yes"
fi

eval "$ac_cv_have_qt"

if test "$have_qt" != yes; then
  AC_MSG_RESULT([$have_qt]);
else
  ac_cv_have_qt="have_qt=yes \
    ac_qt_includes=$ac_qt_includes ac_qt_libraries=$ac_qt_libraries"
  AC_MSG_RESULT([libraries $ac_qt_libraries, headers $ac_qt_includes])
  
  qt_libraries=$ac_qt_libraries
  qt_includes=$ac_qt_includes
  QT_LIBS="-lqt -lXext -lX11 $LIBSOCKET"

ac_cxxflags_safe=$CXXFLAGS
ac_ldflags_safe=$LDFLAGS
ac_libs_safe=$LIBS

  AC_MSG_CHECKING([for qInitPngIo in -lqimgio])
  CXXFLAGS="$CXXFLAGS -I ./ -I $ac_qt_includes"
  LDFLAGS="-L$ac_qt_libraries $X_LDFLAGS"
  LIBS="$QT_LIBS -lqimgio -ljpeg -lpng -lXext -lX11 $LIBSOCKET"
  AC_LANG_CPLUSPLUS
  cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
#include <stdio.h>
#include <qglobal.h>
#include <qpngio.h>
main()
{
  qInitPngIO (); 
  return 0;
}
EOF

  if AC_TRY_EVAL(ac_link) && test -s conftest; then
    rm -f conftest*
    AC_DEFINE(HAVE_QIMGIO)
    QT_LIBS="$QT_LIBS -lqimgio -ljpeg -lpng"
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_WARN([dldialog will not be able to display png images!])
    echo "configure: failed program was:" >&AC_FD_CC
    cat conftest.$ac_ext >&AC_FD_CC
  fi
  rm -f conftest*
  CXXFLAGS=$ac_cxxflags_safe
  LDFLAGS=$ac_ldflags_safe
  LIBS=$ac_libs_safe

fi
AC_SUBST(qt_libraries)
AC_SUBST(qt_includes)

if test "$qt_includes" = "$x_includes"; then
 QT_INCLUDES="";
else
 QT_INCLUDES="-I$qt_includes"
 all_includes="$QT_INCLUDES $all_includes"
fi

if test "$qt_libraries" = "$x_libraries"; then
 QT_LDFLAGS=""
else
 QT_LDFLAGS="-L$qt_libraries"
 all_libraries="$QT_LDFLAGS $all_libraries"
fi

AC_SUBST(QT_INCLUDES)
AC_SUBST(QT_LDFLAGS)
AC_SUBST(QT_LIBS)
AC_PATH_QT_MOC
AC_DEFINE(HAVE_QT)
])

AC_DEFUN(AC_PATH_QT,
[
AC_PATH_QT_1_3
])


## ------------------------------------------------------------------------
## Internal macros to find if we don't need extra flags to find these
## This is not yet used
## ------------------------------------------------------------------------
##
AC_DEFUN(AC_PATH_TV_DIRECT,
[if test "$ac_tv_includes" = NO; then
AC_TRY_CPP([#include <tvision/tvconfig.h>],
[
ac_qt_includes=
],[
])
fi
])

## ------------------------------------------------------------------------
## Try to find the TV headers and libraries.
## $(TV_LDLFLAGS) will be -Ltvliblocation (if needed)
## and $(TV_INCLUDES) will be -Itvhdrlocation (if needed)
## ------------------------------------------------------------------------
##
AC_DEFUN(AC_PATH_TV,
[
ac_tv_libs="-ltvision"

AC_LANG_C
AC_CHECK_LIB(ncurses, initscr, 
             [ ac_tv_libs="$ac_tv_libs -lncurses" ],
	     AC_MSG_ERROR("ncurses library not found!"))

AC_CHECK_LIB(gpm, Gpm_Close, 
             [ ac_tv_libs="$ac_tv_libs -lgpm" ],
	     AC_MSG_ERROR("gpm library not found!"), [ -lncurses ])

AC_MSG_CHECKING([for tvision library])
ac_tv_includes=NO 
ac_tv_libraries=NO
tv_libraries=""
tv_includes=""

AC_ARG_WITH(tvision-dir,
    [  --with-tvision-dir           where the root of tv is installed ],
    [  ac_tv_includes="$withval"/include
       ac_tv_libraries="$withval"/lib
    ])

AC_ARG_WITH(tv-includes,
    [  --with-tvision-includes      where the tv includes are. ],
    [  
       ac_tv_includes="$withval"
    ])
    
AC_ARG_WITH(tv-libraries,
    [  --with-tvision-libraries     where the tv library is installed.],
    [  ac_tv_libraries="$withval"
    ])

if test "$ac_tv_includes" = NO || test "$ac_tv_libraries" = NO; then

AC_CACHE_VAL(ac_cv_have_tv,
AC_PATH_TV_DIRECT
[#try to guess tv locations

tv_incdirs="/usr/lib/tvision/include /usr/local/lib/tvision/include /usr/include/tvision  /usr/local/include /usr/include"
AC_FIND_FILE(tvision/tv.h, $tv_incdirs, tv_incdir)
ac_tv_includes=$tv_incdir

tv_libdirs="/usr/lib/tvision/lib /usr/local/tvision/lib /usr/lib/tvision /usr/local/lib /usr/lib "
AC_FIND_FILE(libtvision.so libtvision.a libtvision.sl, $tv_libdirs, tv_libdir)
ac_tv_libraries=$tv_libdir

ac_cxxflags_safe=$CXXFLAGS
ac_ldflags_safe=$LDFLAGS
ac_libs_safe=$LIBS
CXXFLAGS="$CXXFLAGS -I$tv_incdir"
LDFLAGS="-L$tv_libdir $X_LDFLAGS"
LIBS="$ac_tv_libs"

AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
#define Uses_TApplication
#include <tvision/tvconfig.h>
#include <tvision/tv.h>

class TMyApp : public TApplication
{

public:
TMyApp();

};

TMyApp::TMyApp() :
TProgInit( &TMyApp::initStatusLine,
&TMyApp::initMenuBar,
&TMyApp::initDeskTop
)
{
}

int main()
{
TMyApp myApp;
myApp.run();
return 0;
}
EOF

if AC_TRY_EVAL(ac_link) && test -s conftest; then
  rm -f conftest*
else
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.$ac_ext >&AC_FD_CC
  ac_tv_libraries="NO"
fi
rm -f conftest*
CXXFLAGS=$ac_cxxflags_safe
LDFLAGS=$ac_ldflags_safe
LIBS=$ac_libs_safe

if test "$ac_tv_includes" = NO || test "$ac_tv_libraries" = NO; then
  ac_cv_have_tv="have_tv=no"
  ac_tv_notfound=""
  if test "$ac_tv_includes" = NO; then
    if test "$ac_tv_libraries" = NO; then
      ac_tv_notfound="(headers and libraries)";
    else
      ac_tv_notfound="(headers)";
    fi
  else
    ac_tv_notfound="(libraries)";
  fi

  AC_MSG_ERROR([TVISION $ac_tv_notfound not found. Please check your installation! ]);
else
  have_tv="yes"
fi
])
else
  have_tv="yes"
fi

eval "$ac_cv_have_tv"

if test "$have_tv" != yes; then
  AC_MSG_RESULT([$have_tv]);
else
  ac_cv_have_tv="have_tv=yes \
    ac_tv_includes=$ac_tv_includes ac_tv_libraries=$ac_tv_libraries"
  AC_MSG_RESULT([libraries $ac_tv_libraries, headers $ac_tv_includes])
  
  tv_libraries=$ac_tv_libraries
  tv_includes=$ac_tv_includes
fi

AC_SUBST(tv_libraries)
AC_SUBST(tv_includes)

TV_INCLUDES="-I$tv_includes"
all_includes="$TV_INCLUDES $all_includes"

TV_LDFLAGS="-L$tv_libraries"
TV_LIBS="$ac_tv_libs"

AC_SUBST(TV_INCLUDES)
AC_SUBST(TV_LDFLAGS)
AC_SUBST(TV_LIBS)

AC_DEFINE(HAVE_TVISION)
])

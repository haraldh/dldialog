#!/bin/sh
# Run this to generate all the initial makefiles, etc.

rm -f config.cache

export QTDIR=$(
if [ -z $QTDIR -o ! -e $QTDIR/lib/libqt.so.2 ]; then 
    for i in /usr/lib/qt-2.*;do
	test -e $i/lib/libqt.so.2 && echo $i;
    done
else
    echo $QTDIR
fi
)

test -x $QTDIR/bin/moc && export MOC=$QTDIR/bin/moc

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

THEDIR=`pwd`
cd $srcdir

DIE=0

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "You must have autoconf installed."
	echo "Download the appropriate package for your distribution,"
	echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
	DIE=1
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "You must have automake installed."
	echo "Get ftp://ftp.cygnus.com/pub/home/tromey/automake-1.2d.tar.gz"
	echo "(or a newer version if it is available)"
	DIE=1
}

if test "$DIE" -eq 1; then
	exit 1
fi

if test -z "$*"; then
	echo "I am going to run ./configure with no arguments - if you wish "
        echo "to pass any to it, please specify them on the $0 command line."
fi

case $CC in
xlc )
    am_opt=--include-deps;;
esac

libtoolize --force --copy
autoconf 
#gettextize --copy --force --intl
autoheader
aclocal -I . $ACLOCAL_FLAGS
aclocal
automake --add-missing $am_opt --copy
autoconf 

cd $THEDIR

$srcdir/configure --enable-maintainer-mode "$@"

echo 
echo "Now type 'make'."

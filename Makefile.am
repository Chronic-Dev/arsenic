AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CFLAGS = -O2 -g -Wall -fmessage-length=0 -I/usr/local/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
#LDFLAGS =

lib_LTLIBRARIES = libarsenic-core-2.0.la
library_includedir=$(includedir)/arsenic-2.0
library_include_HEADERS = arsenic/core/common.h arsenic/io/memoryfile.h arsenic/io/dmg.h

libarsenic_core_2_0_la_SOURCES = arsenic/io/memoryfile.cpp arsenic/io/dmg.cpp arsenic/core/common.cpp arsenic/util/plist.cpp arsenic/util/patch.cpp

#bin_PROGRAMS = arsenic
#arsenic_SOURCES = arsenic.cpp

dist_noinst_SCRIPTS = autogen.sh

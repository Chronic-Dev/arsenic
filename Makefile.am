AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CFLAGS = -O2 -g -Wall -fmessage-length=0 -I/usr/local/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
#LDFLAGS =

lib_LTLIBRARIES = libarsenic-core-2.0.0.la
library_includedir=$(includedir)/arsenic-2.0
library_include_HEADERS = arsenic/io/memoryfile.h

libxpwn_hfs_1_0_1_la_SOURCES = 
#libxpwn-hfs_1_0_1la_includedir = $(includedir)/xpwn-hfs
#libxpwn-hfs_1_0_1la_include_HEADERS = core/file.h

libarsenic_core_2_0_0_la_SOURCES = arsenic/io/memoryfile.cpp
#libarsenic-core_2_0_0_la_SOURCE

#bin_PROGRAMS = arsenic
#arsenic_SOURCES = arsenic.cpp

dist_noinst_SCRIPTS = autogen.sh
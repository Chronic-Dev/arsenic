AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

CFLAGS = -O2 -g -Wall -fmessage-length=0 -I../include -I/usr/local/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
#LDFLAGS =

lib_LTLIBRARIES = libxpwn-hfs.1.0.1.a libarsenic-core.2.0.0a libarsenic-util.2.0.0.a libarsenic-io.2.0.0.a
#libxpwn-hfs_1_0_1a_SOURCES = ???
#libarsenic-core_2_0_0a_SOURCES = ??
#libarsenic-util_2_0_0a_SOURCES = ??
#libarsenic-io_2_0_0a_SOURCES = ??

PROGRAMS = arsenic 
#LDFLAGS =

bin_PROGRAMS = arsenic
#arsenic_SOURCES = arsenic.cpp

dist_noinst_SCRIPTS = autogen.sh
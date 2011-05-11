AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libxpwn-hfs.1.0.1.a libarsenic-core.2.0.0a libarsenic-util.2.0.0.a libarsenic-io.2.0.0.a
#libxpwn-hfs_1_0_1a_SOURCES = ???

PROGRAMS = arsenic 
CFLAGS = -O2 -g -Wall -fmessage-length=0 -I../include -I/usr/local/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
#LDFLAGS =

bin_PROGRAMS = arsenic
arsenic_SOURCES = arsenic.cpp bundle.cpp main.cpp memory_file.cpp plist.cpp sha1.cpp image3_element.cpp image3_file.cpp

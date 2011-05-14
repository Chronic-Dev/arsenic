AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CFLAGS = -O2 -g -Wall -fmessage-length=0 -I/usr/local/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
#LDFLAGS =

lib_LTLIBRARIES = libxpwn-hfs-1.0.la
library_includedir=$(includedir)/xpwn-hfs-1.0
library_include_HEADERS = src/abstractfile.h src/checksum.c src/checksum.lo src/checksum.o src/common.h src/dmg.h src/dmgfile.h src/dmglib.h src/filevault.h src/hfscompress.h src/hfslib.h src/hfsplus.h

libxpwn_hfs_1_0_la_SOURCES = src/abstractfile.c src/abstractfile.h src/base64.c src/btree.c src/catalog.c src/checksum.c src/dmgfile.c src/dmglib.c src/extents.c src/fastunicodecompare.c src/filevault.c src/flatfile.c src/hfscompress.c src/hfscompress.h src/hfslib.c src/io.c src/partition.c src/rawfile.c src/resources.c src/udif.c src/utility.c src/volume.c src/xattr.c

dist_noinst_SCRIPTS = autogen.sh

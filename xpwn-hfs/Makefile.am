AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CFLAGS = -O2 -g -Wall -fmessage-length=0 -I./include -I/usr/local/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
#LDFLAGS =

lib_LTLIBRARIES = libxpwn-hfs-1.0.la
library_includedir=$(includedir)/xpwn-hfs-1.0
library_include_HEADERS = includes/xpwn-hfs-1.0/abstractfile.h includes/xpwn-hfs-1.0/common.h includes/xpwn-hfs-1.0/dmg.h includes/xpwn-hfs-1.0/dmgfile.h includes/xpwn-hfs-1.0/dmglib.h includes/xpwn-hfs-1.0/filevault.h includes/xpwn-hfs-1.0/hfscompress.h includes/xpwn-hfs-1.0/hfslib.h includes/xpwn-hfs-1.0/hfsplus.h

libxpwn_hfs_1_0_la_SOURCES = src/abstractfile.c src/abstractfile.h src/base64.c src/btree.c src/catalog.c src/checksum.c src/dmgfile.c src/dmglib.c src/extents.c src/fastunicodecompare.c src/filevault.c src/flatfile.c src/hfscompress.c src/hfscompress.h src/hfslib.c src/io.c src/partition.c src/rawfile.c src/resources.c src/udif.c src/utility.c src/volume.c src/xattr.c

dist_noinst_SCRIPTS = autogen.sh

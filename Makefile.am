AUTOMAKE_OPTIONS = foreign

CFLAGS=-O2 -g -Wall -fmessage-length=0 -I./include -I/usr/local/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
LDFLAGS=-L/usr/local/lib -lX11 -lXtst -lxosd

bin_PROGRAMS = arsenic
arsenic_SOURCES = arsenic.cpp bundle.cpp main.cpp memoryfile.cpp plist.cpp
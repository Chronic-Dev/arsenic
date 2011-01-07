CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I./include

DIRS = Source include

SRC = $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))

OBJDIR = bin/
OBJS =		$(patsubst %.cpp,%.o,$(SRC))

LIBS = -lxml2 -lcrypto

TARGET = arsenic

#$(TARGET):	$(OBJS)
#	@echo 'Linking $(TARGET)'
#	@$(CXX) -o $(OBJDIR)$(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	@echo 'Compiling $@'
	@$(CXX) -c $(CXXFLAGS) $< -o $@

all:
	@echo 'Arsenic, requires you run make with a platform argument (win, linux, mach) or clean'

header:
	@echo ''
	@echo 'GreenPois0n Arsenic'
	@echo 'Copyright (C) 2010 Chronic-Dev Team'
	@echo ''
	@echo 'This program is free software: you can redistribute it and/or modify'
	@echo 'it under the terms of the GNU General Public License as published by'
	@echo 'the Free Software Foundation, either version 3 of the License, or'
	@echo '(at your option) any later version.'
	@echo ''
	@mkdir -p $(OBJDIR)

mach: header $(OBJS)
	@echo 'Linking $(TARGET)'
	@$(CXX) -o $(OBJDIR)$(TARGET) $(OBJS) $(LIBS)

linux: header
	@echo 'TODO'

win: header
	@echo 'TODO'

clean:
	@rm -rf bin/
	@mkdir bin
	@rm -f $(OBJS) $(TARGET)

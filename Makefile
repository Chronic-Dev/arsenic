CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I./include

DIRS = src include

SRC = $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))

OBJS =		$(patsubst %.cpp,%.o,$(SRC))

LIBS =

TARGET =	bin/arsenic

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

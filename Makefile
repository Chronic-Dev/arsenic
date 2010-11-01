CXXFLAGS = -O0 -g -Wall -fmessage-length=0

INCLUDE = -I./include -I"/usr/local/include" -L"/usr/local/lib"
LIBS = -lcrypto
TARGET = ./bin/arsenic

DIRS = ./src ./includes
SOURCE :=	$(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))
HEADERS :=	$(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.h))
EXTRA = ./Makefile

all:    $(SOURCE)
	$(CXX) -o $(TARGET) $(SOURCE) $(INCLUDE) $(LIBS) $(CXXFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)

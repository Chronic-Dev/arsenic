CXXFLAGS = -O0 -g -Wall -fmessage-length=0
OBJS = main.o Array.o Arsenic.o Common.o Data.o Date.o Dictionary.o File.o Firmware.o Folder.o Image3Element.o Image3File.o MemoryFile.o PList.o Real.o RootNode.o SHA1.o String.o URL.o ZipFile.o
INCLUDE = -I./include
LIBS = -lcrypto
TARGET = arsenic

%.o: %.cpp
	$(CXX) -c $(<) -o $(@) $(INCLUDE) $(CXXFLAGS)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(INCLUDE) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

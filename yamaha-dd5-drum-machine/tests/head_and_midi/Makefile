default: all

CFLAGS := -Wall -D__LINUX_ALSA__ -I./include -I../include -I../../include -I/etc/dynamixel-ach/include/
CC := g++

BINARIES := main

SRC := src/main.cpp src/RtMidi.cpp

LIBS := -lrt -lstdc++ -lach -lasound -lpthread

all: src/main.cpp 
	$(CC) $(CFLAGS) -o $(BINARIES) $(SRC) $(LIBS)

clean:
	rm -f $(BINARIES) src/*.o


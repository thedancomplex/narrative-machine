default: all

CFLAGS := -I./include -I/etc/dynamixel-ach/include/ -Wall
CC := g++

BINARIES := main
all : $(BINARIES)

LIBS := -lrt -lstdc++ -lach

OBJS = src/main.o      \
       src/Sequencer.o 

$(BINARIES): $(OBJS)
	$(CC) -o $@ $< $(LIBS)  
#	$(CC) -o $@ $< $(LIBS) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(BINARIES) src/*.o


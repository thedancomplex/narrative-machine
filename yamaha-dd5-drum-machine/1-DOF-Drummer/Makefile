default: all

CFLAGS := -I./include -I/etc/dynamixel-ach/include/ -Wall
CC := g++

BINARIES := dynamixel-ach-simple-demo-cpp
all : $(BINARIES)

LIBS := -lrt -lstdc++ -lach

$(BINARIES): src/main.o
	gcc -o $@ $< $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(BINARIES) src/*.o


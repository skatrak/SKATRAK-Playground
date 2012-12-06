# MAKEFILE PARA COMPILAR EN UBUNTU
# ESCRITO POR SERGIO M. AFONSO FUMERO (theSkatrak@gmail.com)

ARCH := $(shell getconf LONG_BIT)

CC=g++
CFLAGS=-Wall -c -I../include
LIBSPATH32=../lib/linux/x86
LIBSPATH64=../lib/linux/x64
LDFLAGS=-L$(LIBSPATH$(ARCH)) -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
SOURCES=../src/main.cpp ../src/music.cpp ../src/system.cpp ../src/image.cpp ../src/timekeeper.cpp ../src/font.cpp ../src/inifile.cpp ../src/sfx.cpp ../src/str_operations.cpp ../src/main.cpp ../src/mainMenu.cpp
OBJECTS=../bin/linux/obj/main.o ../bin/linux/obj/music.o ../bin/linux/obj/system.o ../bin/linux/obj/image.o ../bin/linux/obj/timekeeper.o ../bin/linux/obj/font.o ../bin/linux/obj/inifile.o ../bin/linux/obj/sfx.o ../bin/linux/obj/str_operations.o ../bin/linux/obj/menu.o ../bin/linux/obj/mainMenu.o
EXECUTABLE=../bin/linux/SKATRAK-Playground

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -O2 $(OBJECTS) -o $@ $(LDFLAGS)

../bin/linux/obj/main.o:
	$(CC) $(CFLAGS) ../src/main.cpp -o $@

../bin/linux/obj/music.o:
	$(CC) $(CFLAGS) ../src/music.cpp -o $@

../bin/linux/obj/system.o:
	$(CC) $(CFLAGS) ../src/system.cpp -o $@

../bin/linux/obj/image.o:
	$(CC) $(CFLAGS) ../src/image.cpp -o $@

../bin/linux/obj/timekeeper.o:
	$(CC) $(CFLAGS) ../src/timekeeper.cpp -o $@

../bin/linux/obj/font.o:
	$(CC) $(CFLAGS) ../src/font.cpp -o $@

../bin/linux/obj/inifile.o:
	$(CC) $(CFLAGS) ../src/inifile.cpp -o $@

../bin/linux/obj/sfx.o:
	$(CC) $(CFLAGS) ../src/sfx.cpp -o $@

../bin/linux/obj/str_operations.o:
	$(CC) $(CFLAGS) ../src/str_operations.cpp -o $@

../bin/linux/obj/menu.o:
	$(CC) $(CFLAGS) ../src/menu.cpp -o $@

../bin/linux/obj/mainMenu.o:
	$(CC) $(CFLAGS) ../src/mainMenu.cpp -o $@

clean:
	rm -f ../bin/linux/obj/*.o


# MAKEFILE PARA COMPILAR EN UBUNTU
# ESCRITO POR SERGIO M. AFONSO FUMERO (theSkatrak@gmail.com)

CC=g++
CFLAGS=-Wall -c -I../include
LDFLAGS=-L../lib -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
SOURCES=../src/main.cpp ../src/music.cpp ../src/system.cpp ../src/image.cpp ../src/timekeeper.cpp ../src/font.cpp ../src/inifile.cpp ../src/sfx.cpp ../src/str_operations.cpp
OBJECTS=../bin/linux/obj/main.o ../bin/linux/obj/music.o ../bin/linux/obj/system.o ../bin/linux/obj/image.o ../bin/linux/obj/timekeeper.o ../bin/linux/obj/font.o ../bin/linux/obj/inifile.o ../bin/linux/obj/sfx.o ../bin/linux/obj/str_operations.o
EXECUTABLE="../bin/linux/SKATRAK-Playground"

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

clean:
	rm -f "../bin/linux/*.o"

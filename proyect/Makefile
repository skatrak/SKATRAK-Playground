CC=g++
CFLAGS=-c
LDFLAGS=-lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
SOURCES=../src/image.cpp ../src/main.cpp ../src/music.cpp ../src/system.cpp ../src/timekeeper.cpp
OBJECTS=../bin/linux/obj/image.o ../bin/linux/obj/main.o ../bin/linux/obj/music.o ../bin/linux/obj/system.o ../bin/linux/obj/timekeeper.o
EXECUTABLE="../bin/linux/SKATRAK-Playground"

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -O2 $(OBJECTS) -o $@ $(LDFLAGS)

../bin/linux/obj/image.o:
	$(CC) $(CFLAGS) ../src/image.cpp -o $@

../bin/linux/obj/main.o:
	$(CC) $(CFLAGS) ../src/main.cpp -o $@

../bin/linux/obj/music.o:
	$(CC) $(CFLAGS) ../src/music.cpp -o $@

../bin/linux/obj/system.o:
	$(CC) $(CFLAGS) ../src/system.cpp -o $@

../bin/linux/obj/timekeeper.o:
	$(CC) $(CFLAGS) ../src/timekeeper.cpp -o $@

clean:
	rm -f "../bin/linux/*.o"


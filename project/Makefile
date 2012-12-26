# MAKEFILE PARA COMPILAR EN UBUNTU
# ESCRITO POR SERGIO M. AFONSO FUMERO (theSkatrak@gmail.com)

ARCH := $(shell getconf LONG_BIT)

CC=g++
CFLAGS=-Wall -c -I../include
LIBSPATH32=../lib/linux/x86
LIBSPATH64=../lib/linux/x64
LDFLAGS=-L$(LIBSPATH$(ARCH)) -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
SOURCES=../src/main.cpp ../src/music.cpp ../src/system.cpp ../src/image.cpp ../src/timekeeper.cpp ../src/font.cpp ../src/inifile.cpp ../src/sfx.cpp ../src/str_operations.cpp ../src/menu.cpp ../src/mainMenu.cpp ../src/conecta4/tablero.cpp ../src/conecta4/mainConecta4.cpp ../src/conecta4/Game_Conecta4.cpp
OBJECTS=../bin/linux/obj/main.o ../bin/linux/obj/music.o ../bin/linux/obj/system.o ../bin/linux/obj/image.o ../bin/linux/obj/timekeeper.o ../bin/linux/obj/font.o ../bin/linux/obj/inifile.o ../bin/linux/obj/sfx.o ../bin/linux/obj/str_operations.o ../bin/linux/obj/menu.o ../bin/linux/obj/mainMenu.o ../bin/linux/obj/tablero.o ../bin/linux/obj/mainConecta4.o ../bin/linux/obj/Game_Conecta4.o
EXECUTABLE=../bin/linux/SKATRAK-Playground

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Compilando ejecutable...
	@$(CC) -O2 $(OBJECTS) -o $@ $(LDFLAGS)

../bin/linux/obj/main.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/main.cpp -o $@

../bin/linux/obj/music.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/music.cpp -o $@

../bin/linux/obj/system.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/system.cpp -o $@

../bin/linux/obj/image.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/image.cpp -o $@

../bin/linux/obj/timekeeper.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/timekeeper.cpp -o $@

../bin/linux/obj/font.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/font.cpp -o $@

../bin/linux/obj/inifile.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/inifile.cpp -o $@

../bin/linux/obj/sfx.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/sfx.cpp -o $@

../bin/linux/obj/str_operations.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/str_operations.cpp -o $@

../bin/linux/obj/menu.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/menu.cpp -o $@

../bin/linux/obj/mainMenu.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/mainMenu.cpp -o $@

../bin/linux/obj/tablero.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/conecta4/tablero.cpp -o $@

../bin/linux/obj/mainConecta4.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/conecta4/mainConecta4.cpp -o $@

../bin/linux/obj/Game_Conecta4.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) ../src/conecta4/Game_Conecta4.cpp -o $@

clean:
	rm -f ../bin/linux/obj/*.o

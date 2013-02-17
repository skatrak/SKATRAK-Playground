# MAKEFILE PARA COMPILAR EN UBUNTU
# ESCRITO POR SERGIO M. AFONSO FUMERO (theSkatrak@gmail.com)

# Para determinar qué librerías (x86, x64) utilizar
ARCH := $(shell getconf LONG_BIT)

# Argumentos para el compilador
CC=g++
CFLAGS=-Wall -c -I../include
LIBSPATH32=../lib/linux/x86
LIBSPATH64=../lib/linux/x64
LDFLAGS=-L$(LIBSPATH$(ARCH)) -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

# Directorios importantes
OBJPATH=../bin/linux/obj
SRCPATH=../src

# Rutas de los archivos
SOURCES=$(SRCPATH)/main.cpp $(SRCPATH)/music.cpp $(SRCPATH)/system.cpp $(SRCPATH)/image.cpp $(SRCPATH)/timekeeper.cpp $(SRCPATH)/font.cpp $(SRCPATH)/inifile.cpp $(SRCPATH)/sfx.cpp $(SRCPATH)/str_operations.cpp $(SRCPATH)/menu.cpp $(SRCPATH)/mainMenu.cpp $(SRCPATH)/messagebox.cpp $(SRCPATH)/conecta4/tablero.cpp $(SRCPATH)/conecta4/mainConecta4.cpp $(SRCPATH)/conecta4/gameConecta4.cpp $(SRCPATH)/conecta4/messagesConecta4.cpp $(SRCPATH)/snake/mainSnake.cpp $(SRCPATH)/snake/snakePiece.cpp $(SRCPATH)/snake/snake.cpp
OBJECTS=$(OBJPATH)/main.o $(OBJPATH)/music.o $(OBJPATH)/system.o $(OBJPATH)/image.o $(OBJPATH)/timekeeper.o $(OBJPATH)/font.o $(OBJPATH)/inifile.o $(OBJPATH)/sfx.o $(OBJPATH)/str_operations.o $(OBJPATH)/menu.o $(OBJPATH)/mainMenu.o $(OBJPATH)/messagebox.o $(OBJPATH)/tablero.o $(OBJPATH)/mainConecta4.o $(OBJPATH)/gameConecta4.o $(OBJPATH)/messagesConecta4.o $(OBJPATH)/mainSnake.o $(OBJPATH)/snakePiece.o $(OBJPATH)/snake.o
EXECUTABLE=../bin/linux/SKATRAK-Playground

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Compilando ejecutable...
	@$(CC) -O2 $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJPATH)/main.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/main.cpp -o $@

$(OBJPATH)/music.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/music.cpp -o $@

$(OBJPATH)/system.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/system.cpp -o $@

$(OBJPATH)/image.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/image.cpp -o $@

$(OBJPATH)/timekeeper.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/timekeeper.cpp -o $@

$(OBJPATH)/font.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/font.cpp -o $@

$(OBJPATH)/inifile.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/inifile.cpp -o $@

$(OBJPATH)/sfx.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/sfx.cpp -o $@

$(OBJPATH)/str_operations.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/str_operations.cpp -o $@

$(OBJPATH)/menu.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/menu.cpp -o $@

$(OBJPATH)/mainMenu.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/mainMenu.cpp -o $@

$(OBJPATH)/messagebox.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/messagebox.cpp -o $@

# CONECTA 4

$(OBJPATH)/tablero.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/conecta4/tablero.cpp -o $@

$(OBJPATH)/mainConecta4.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/conecta4/mainConecta4.cpp -o $@

$(OBJPATH)/gameConecta4.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/conecta4/gameConecta4.cpp -o $@

$(OBJPATH)/messagesConecta4.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/conecta4/messagesConecta4.cpp -o $@

# SNAKE

$(OBJPATH)/mainSnake.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/snake/mainSnake.cpp -o $@

$(OBJPATH)/snakePiece.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/snake/snakePiece.cpp -o $@

$(OBJPATH)/snake.o:
	@echo "Compilando \"$@\"..."
	@$(CC) $(CFLAGS) $(SRCPATH)/snake/snake.cpp -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJPATH)/*.o

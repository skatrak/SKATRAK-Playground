/*
 *  This file is part of SKATRAK Playground.
 *
 *  SKATRAK Playground is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/> or
 *  write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 *  Floor, Boston, MA 02110-1301 USA
 *
 *  Sergio M. Afonso Fumero <theSkatrak@gmail.com>
 */

#include <SKATRAK_PLAYGROUND.hpp>
#include <shared_attributes.hpp>

/* Definiciones de las rutas por defecto de los recursos */
const char* MUS_PATH = "../../resources/sound/";
const char* SFX_PATH = "../../resources/sound/SFX/";
const char* FONT_PATH = "../../resources/fonts/";
const char* IMG_PATH = "../../resources/images/";
const char* INI_PATH = "../../resources/settings/";

/* Prototipo del menú principal */
returnVal mainMenu();
void tryIni(void);

system_t* sistema = NULL;			// La variable sistema se comparte entre todos los minijuegos y permanece igual para todos ellos.
music_t* musica = NULL;				// La variable musica se comparte por todos los minijuegos y cada uno puede tener su propia lista de reproducción.

int main(int argc, char* argv[]){
	// Prueba de lectura en un archivo .ini
	tryIni();
	// Creamos la variable sistema (Iniciamos SDL)
	sistema = new system_t(1024, 768, 32);
	sistema->setIcon("icono_prueba.png");

	// Cargamos 3 pistas de música para que reproduzcan en el fondo
	musica = new music_t(3);
	musica->setVol(128);
	musica->setTrack(0, "track01.ogg");
	musica->setTrack(1, "track02.ogg");
	musica->setTrack(2, "track03.ogg");

	// Activamos la repetición de teclas para los menús (Los juegos que no usen esta funcionalidad la tienen que volver a activar al salir)
	SDL_EnableKeyRepeat(250, 75);

	// Imágenes para mostrar en el menú inicio
	SDL_Surface* screen = sistema->scr();
	if(screen == NULL){
		fprintf(stderr, "La pantalla no se ha iniciado. Saliendo del programa...\n");
		return 1;
	}
	image_t fondo("Fondo_inicio_prueba.png");
	font_t nombreJuego("font01.ttf");
	nombreJuego.setSize(72);
	nombreJuego.setText("SKATRAK Playground");
	font_t empezar("font01.ttf");
	empezar.setSize(32);
	empezar.setText("Pulse una tecla para comenzar");
	timekeeper_t temporizador;

	// Variables para controlar el game loop
	SDL_Event event;
	bool salir = false;

	// Comenzamos a reproducir la música
	musica->play();

	int alpha = 0;
	while((int)alpha < SDL_ALPHA_OPAQUE){
		temporizador.refresh();
		nombreJuego.setAlpha((int)alpha);
		fondo.blit(0, 0, screen);
		nombreJuego.blit((int)(screen->w / 2) - (int)(nombreJuego.width() / 2), (int)(screen->h / 2) - (int)(nombreJuego.height() / 2), screen);
		sistema->update();
		temporizador.waitFramerate(30);
		alpha += 3;
		while(SDL_PollEvent(&event)); // Vaciamos la cola de eventos para que no se propaguen por otros menús
	}
	nombreJuego.setAlpha(SDL_ALPHA_OPAQUE);

	bool alphaAdd = false;
	while(!salir){
		// Reiniciamos el temporizador en cada ciclo
		temporizador.refresh();
		// Gestionamos los eventos
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYDOWN:
					if(mainMenu() == ERROR)
						fprintf(stderr, "Se ha salido del programa con un error.\n");
					salir = true;
					break;
				case SDL_QUIT:
					salir = true;
			}
		}
		// Para dar una sensación de texto parpadeante
		if(alphaAdd)
			alpha += 5;
		else
			alpha -= 5;
		if(alpha <= SDL_ALPHA_TRANSPARENT) alphaAdd = true;
		else if(alpha >= SDL_ALPHA_OPAQUE - 5) alphaAdd = false;
		empezar.setAlpha((int)alpha);

		// Imprimimos por pantalla todo lo que haga falta e intercambiamos los buffers de vídeo
		fondo.blit(0, 0, screen);
		nombreJuego.blit((int)(screen->w / 2) - (int)(nombreJuego.width() / 2), (int)(screen->h / 2) - (int)(nombreJuego.height() / 2), screen);
		empezar.blit((int)(screen->w / 2) - (int)(empezar.width() / 2), (int)(3 * screen->h / 4) - (int)(empezar.height() / 2), screen);
		if(!salir)
			sistema->update();	// Esto es para que no se muestre la pantalla de inicio al salir

		// Fijamos los FPS a 30
		temporizador.waitFramerate(30);
	}

	// Paramos la música antes de salir y liberamos recursos
	musica->halt();
	if(musica != NULL)
		delete musica;
	if(sistema != NULL)
		delete sistema;
	return 0;
}

/* FUNCIÓN PARA PROBAR EL FUNCIONAMIENTO DE LOS ARCHIVOS .INI */
void tryIni(void){
	inifile_t prueba("prueba.ini");
	string cadenas[3];
	int enteros[4];
	double decimales[3];
	bool booleanos[4];
	// Lectura de cadenas
	cadenas[0] = prueba.readString("Strings", "cad1");
	cadenas[1] = prueba.readString("Strings", "cad2");
	cadenas[2] = prueba.readString("Strings", "cad3");
	// Lectura de enteros
	enteros[0] = prueba.readInt("Integers", "numero1");
	enteros[1] = prueba.readInt("Integers", "numero2");
	enteros[2] = prueba.readInt("Integers", "numero3");
	enteros[3] = prueba.readInt("Integers", "numero4");
	// Lectura de decimales
	decimales[0] = prueba.readDouble("Floats", "numero1");
	decimales[1] = prueba.readDouble("Floats", "numero2");
	decimales[2] = prueba.readDouble("Floats", "numero3");
	// Lectura de booleanos
	booleanos[0] = prueba.readBool("Bools", "booleano1");
	booleanos[1] = prueba.readBool("Bools", "booleano2");
	booleanos[2] = prueba.readBool("Bools", "booleano3");
	booleanos[3] = prueba.readBool("Bools", "booleano4");
	// Comprobación de los resultados
	int i;
	printf("PRUEBA DE LECTURA EN .INI:\n");
	for(i = 0; i < 3; i++)
		printf("Cadena %d: %s\n", i+1, cadenas[i].c_str());
	printf("\n");
	for(i = 0; i < 4; i++)
		printf("Entero %d: %d\n", i+1, enteros[i]);
	printf("\n");
	for(i = 0; i < 3; i++)
		printf("Decimal %d: %lf\n", i+1, decimales[i]);
	printf("\n");
	for(i = 0; i < 4; i++){
		printf("Booleano %d: ", i+1);
		if(booleanos[i])
			printf("Verdadero");
		else
			printf("Falso");
		printf("\n");
	}
	printf("\n");
}

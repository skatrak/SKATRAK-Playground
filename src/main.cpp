#include "../include/SKATRAK_PLAYGROUND.hpp"
#include "../include/shared_attributes.hpp"

/* Definiciones de las rutas por defecto de los recursos */
const char* MUS_PATH = "../../resources/sound/";
const char* SFX_PATH = "../../resources/sound/";
const char* FONT_PATH = "../../resources/fonts/";
const char* IMG_PATH = "../../resources/images/";
const char* INI_PATH = "../../resources/settings/";

/* Prototipos de los menús de los distintos minijuegos */
returnVal mainMenu();
//returnVal main3enRaya();
//returnVal mainConecta4();
//returnVal mainPong();
//[...]

system_t* sistema = NULL;			// La variable sistema se comparte entre todos los minijuegos y permanece igual para todos ellos.
music_t* musica = NULL;				// La variable musica se comparte por todos los minijuegos y cada uno puede tener su propia lista de reproducción.

int main(int argc, char* argv[]){
	// Creamos la variable sistema (Iniciamos SDL)
	sistema = new system_t(1024, 768, 32);
	sistema->setIcon("icono_prueba.png");

	// Cargamos 3 pistas de música para que reproduzcan en el fondo
	musica = new music_t(3);
	musica->setVol(128);
	musica->setTrack(0, "track01.ogg");
	musica->setTrack(1, "track02.ogg");
	musica->setTrack(2, "track03.ogg");

	// Imágenes para mostrar en el menú inicio
	SDL_Surface* screen = sistema->scr();
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
		SDL_PollEvent(NULL);
	}

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
		// Para dar una sensación de texto parpadeante (Cuando funcionen las transparencias)
		if(alphaAdd)
			alpha += 5;
		else
			alpha -= 5;
		if(alpha <= SDL_ALPHA_TRANSPARENT) alphaAdd = true;
		else if(alpha >= SDL_ALPHA_OPAQUE) alphaAdd = false;
		empezar.setAlpha((int)alpha);

		// Imprimimos por pantalla todo lo que haga falta e intercambiamos los buffers de vídeo
		fondo.blit(0, 0, screen);
		nombreJuego.blit((int)(screen->w / 2) - (int)(nombreJuego.width() / 2), (int)(screen->h / 2) - (int)(nombreJuego.height() / 2), screen);
		empezar.blit((int)(screen->w / 2) - (int)(empezar.width() / 2), (int)(3 * screen->h / 4) - (int)(empezar.height() / 2), screen);
		sistema->update();

		// Fijamos los FPS a 30
		temporizador.waitFramerate(30);
	}

	// Paramos la música antes de salir y liberamos recursos
	musica->halt();
	printf("El programa ha estado abierto %d segundos y ha imprimido %d fotogramas.\n", (int)temporizador.elapsed()/1000, temporizador.renderedFrames());
	if(musica != NULL)
		delete musica;
	if(sistema != NULL)
		delete sistema;
	return 0;
}

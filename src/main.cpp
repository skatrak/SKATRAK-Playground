#include <string>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "../include/system.hpp"
#include "../include/music.hpp"
#include "../include/image.hpp"
#include "../include/timekeeper.hpp"
#include "../include/font.hpp"
#include "../include/inifile.hpp"

SDL_Event event;
inifile_t pruebaIni("../../resources/settings/prueba.ini");
system_t sistema(1024, 768, 32);	// La variable sistema se comparte entre todos los minijuegos y permanece igual para todos ellos.
music_t musica(3);					// La variable musica se comparte por todos los minijuegos y cada uno puede tener su propia lista de reproducción.

/**
 * @brief Esta función hace que se pase automáticamente a la siguiente canción de la lista de reproducción cuando se acaba la que se está reproduciendo.
 * @note Se supone que esta función tiene que ser miembro de la clase music_t, pero la llamada a la función Mix_HookMusicFinished de SDL requiere que se le pase
 * como único argumento la dirección de una función que no reciba ni devuelva ningún valor. Si estuviera implementada como método de la clase music_t,
 * recibiría un parámetro oculto y no se podría compilar.
 */
void nextTrack(){
	if(musica.playing)
		musica.halt();
	musica.current++;
	if(musica.current >= musica.n_tracks)
		musica.current = 0;
	musica.playing = false;
	musica.play();
}

int main(int argc, char* argv[]){
	// Ponemos un icono a la ventana
	sistema.setIcon("../../resources/images/icono_prueba.png");
	// Cargamos 3 pistas de música para que reproduzcan en el fondo
	musica.setVol(128);
	musica.setTrack(0, "../../resources/sound/track01.ogg");
	musica.setTrack(1, "../../resources/sound/track02.ogg");
	musica.setTrack(2, "../../resources/sound/track03.ogg");
	// Cargamos y mostramos por pantalla una imagen de prueba
	image_t prueba("../../resources/images/icono_prueba.png");
	// Creamos el temporizador
	timekeeper_t temporizador;
	// Creamos dos fuentes, les asignamos un tamaño, un estilo y un texto
	font_t fuente;
	font_t fuente2("../../resources/fonts/font01.ttf");

	fuente.open("../../resources/fonts/font01.ttf");
	fuente.setSize(64);
	fuente2.setSize(32);
	fuente.setStyle(TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);
	fuente2.setStyle(TTF_STYLE_BOLD);
	fuente.setText(pruebaIni.readString("Other", "Text1"));
	fuente2.setText(pruebaIni.readString("Other", "Text2"));
	fuente2.setColor(255, 255, 0);

	bool salir = false;
	// Comenzamos a reproducir la música
	musica.play();
	// GAME LOOP
	while(!salir){
		// Reiniciamos el temporizador en cada ciclo del game loop
		temporizador.refresh();
		// Gestionamos los eventos
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE) salir = true;
					if(event.key.keysym.sym == SDLK_RIGHT) nextTrack();
					break;
				case SDL_QUIT:
					salir = true;
			}
		}
		// Ponemos un color aleatorio a las letras en cada fotograma
		fuente.setColor(rand() % 256, rand() % 256, rand() % 256);
		// Imprimimos por pantalla todo lo que haga falta e intercambiamos los buffers de vídeo
		fuente.blit(200, 200, sistema.scr());
		fuente2.blit(200 + (int)fuente.width()/2, 200 + fuente.height(), sistema.scr());	// Colocamos esta línea debajo de la anterior y separada horizontalmente
		prueba.blit(100, 100, sistema.scr());
		sistema.update();
		// Fijamos los FPS a 30
		temporizador.waitFramerate(30);
	}
	// Paramos la música antes de salir. No hay que liberar memoria porque se libera en los destructores de las clases
	musica.halt();
	printf("El programa ha estado abierto %d segundos y ha imprimido %d fotogramas.\n", (int)temporizador.elapsed()/1000, temporizador.renderedFrames());
	return 0;
}

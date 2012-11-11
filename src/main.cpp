#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "../include/system.hpp"
#include "../include/music.hpp"

SDL_Event event;
system_t sistema(1024, 768, 32);	//! La variable sistema se comparte entre todos los minijuegos y permanece igual para todos ellos.
music_t musica(3);					//! La variable musica se comparte por todos los minijuegos y cada uno puede tener su propia lista de reproducción.

/**
 * @brief Esta función hace que se pase automáticamente a la siguiente canción de la lista de reproducción cuando se acaba la que se está reproduciendo.
 * @note Se supone que esta función tiene que ser miembro de la clase music_t, pero la llamada a la función Mix_HookMusicFinished de SDL requiere que se le pase
 * una dirección de tipo función y no de tipo miembro.
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
	sistema.setIcon("../resources/images/icono_prueba.png");
	musica.setVol(128);
	musica.setTrack(0, "../resources/sound/track01.ogg");
	musica.setTrack(1, "../resources/sound/track02.ogg");
	musica.setTrack(2, "../resources/sound/track03.ogg");

	musica.play();
	while(true){
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE) return 0;
					if(event.key.keysym.sym == SDLK_RIGHT) nextTrack();
					break;
				case SDL_QUIT:
					return 0;
			}
			SDL_Delay(100);
			sistema.update();
		}
	}
	musica.halt();
}

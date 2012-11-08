#include <string>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"
#include "../include/SDL/SDL_mixer.h"
#include "../include/SDL/SDL_ttf.h"

#include "../include/system.hpp"
#include "../include/music.hpp"

system_t sistema(1024, 768, 32);
music_t musica;

/**
 * @brief Esta función hace que se pase automáticamente a la siguiente canción de la lista de reproducción cuando se acaba la que se está reproduciendo.
 * @note Se supone que esta función tiene que ser miembro de la clase music_t, pero la llamada a la función Mix_HookMusicFinished de SDL requiere que se le pase
 * una dirección de tipo función y no de tipo miembro.
 */
void nextTrack(){
	musica.current++;
	if(musica.current >= musica.n_tracks)
		musica.current = 0;
	musica.playing = false;
	musica.play();
}

int main(int argc, char* argv[]){
	sistema.toggleFullscreen();
	sistema.update();
	SDL_Delay(5000);
	sistema.toggleFullscreen();
	sistema.update();
	SDL_Delay(5000);
}

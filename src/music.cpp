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

/* Inclusión de cabeceras necesarias */
// Cabecera de la clase
#include "music.hpp"
// Estándar
#include <string>
using std::string;
// SDL
#include "SDL/SDL_mixer.h"
// Propias
#include "SKATRAK_PLAYGROUND.hpp"
#include "system.hpp"

/* Declaración de la variable musica que será la que contenga la lista de reproducción */
extern music_t* musica;

/**
 * @brief Esta función hace que se pase automáticamente a la siguiente canción de la lista de reproducción cuando se acaba la que se está reproduciendo.
 * @note Se supone que esta función tiene que ser miembro de la clase music_t, pero la llamada a la función Mix_HookMusicFinished de SDL requiere que se le pase
 * como único argumento la dirección de una función que no reciba ni devuelva ningún valor. Si estuviera implementada como método de la clase music_t,
 * recibiría un parámetro oculto y no se podría compilar.
 */
void nextTrack(){
	if(musica->playing)
		musica->halt();
	musica->current++;
	if(musica->current >= musica->n_tracks)
		musica->current = 0;
	musica->playing = false;
	musica->play();
}

/**
 * @brief Inicializa la clase con los valores por defecto e inicia SDL_mixer.
 *
 * También reserva espacio para AUDIO_CHANNELS canales de audio para reproducir efectos de sonido.
 * @see sfx_t
 */
music_t::music_t(): music(NULL), music_names(NULL), n_tracks(0), volume(128), current(0), running(false), playing(false), paused(false) {
	if(sistema->initSubsystems(SYS_SUBST_MIX) & SYS_SUBST_MIX){
		running = true;
		Mix_HookMusicFinished(nextTrack);
	}
}

/**
 * @brief Inicializa la clase con los valores por defecto, inicia SDL_mixer y reserva espacio para un número de canciones.
 * @param nT Número de canciones que deseas poder reproducir cíclicamente.
 *
 * También reserva espacio para AUDIO_CHANNELS canales de audio para reproducir efectos de sonido.
 * @see sfx_t
 */
music_t::music_t(int nT): music(NULL), music_names(NULL), n_tracks(nT), volume(128), current(0), running(false), playing(false), paused(false) {
	if(sistema->initSubsystems(SYS_SUBST_MIX) & SYS_SUBST_MIX){
		running = true;
		setTracks(n_tracks);
		Mix_HookMusicFinished(nextTrack);
	}
}

/**
 * @brief Destructor. Libera la memoria ocupada por todas las canciones.
 */
music_t::~music_t(){
	if(playing)
		halt();
	if(music != NULL){
		for(int i = 0; i < n_tracks; i++)
			Mix_FreeMusic(music[i]);
		delete [] music;
		music = NULL;
		Mix_HookMusicFinished(NULL);
	}
	if(music_names != NULL)
		delete [] music_names;
}

/**
 * @brief Reserva espacio para un número determinado de canciones. Borra la información la lista de reproducción actual
 * aunque se especifique el mismo número.
 * @param n Número de canciones que se van a reservar.
 * @note Para evitar errores en tiempo de ejecución, hay que llenar este array completamente con music_t::setTrack.
 */
void music_t::setTracks(int n){
	if(playing)
		halt();
	if(music != NULL){
		for(int i = 0; i < n_tracks; i++){
			if(music[i] != NULL){
				Mix_FreeMusic(music[i]);
				music[i] = NULL;
			}
		}
		delete [] music;
		music = NULL;
	}
	if(music_names != NULL){
		delete [] music_names;
		music_names = NULL;
	}
	n_tracks = n;
	music = new Mix_Music*[n_tracks];
	if(music == NULL){
		fprintf(stderr, "music_t::setTracks: Error en la reserva de memoria para la lista de reproducción.\n");
		return;
	}
	for(int i = 0; i < n_tracks; i++)
		music[i] = NULL;

	music_names = new string[n_tracks];
	if(music_names == NULL){
		fprintf(stderr, "music_t::setTracks: Error en la reserva de memoria para los nombres de las canciones.\n");
		delete [] music;
		music = NULL;
	}
}

/**
 * @brief Carga una canción en un índice del array de la lista de reproducción.
 * @param index Posición en la lista de reproducción (Entre 0 y n-1).
 * @param path Ruta del fichero donde está guardada la canción.
 * @note Para llamar a esta función hay que llamar previamente a music_t::setTracks para reservar la memoria.
 */
void music_t::setTrack(int index, string path){
	if(playing)
		halt();
	if(index < 0 || index >= n_tracks){
		fprintf(stderr, "music_t::setTrack: Se ha intentado cargar una canción en una zona de memoria no reservada. Se sobreescribirá la primera canción.\n");
		index = 0;
	}
	if(music != NULL && music_names != NULL){
		string compPath = MUS_PATH;
		compPath += path;
		music_names[index] = compPath;
		if(music[index] != NULL){
			Mix_FreeMusic(music[index]);
			music[index] = NULL;
		}
		music[index] = Mix_LoadMUS(compPath.c_str());
		if(music[index] == NULL)
			fprintf(stderr, "music_t::setTrack: No se ha podido cargar el fichero \"%s\": %s.\n", compPath.c_str(), Mix_GetError());
	}
	else
		fprintf(stderr, "music_t::setTrack: No se puede cargar ninguna canción en memoria porque no se ha reservado previamente.\n");
}

/**
 * @brief Si el sistema de audio está iniciado correctamente y la música no se está reproduciendo, se comienza a reproducir.
 * Si la música está pausada, se reanuda.
 */
void music_t::play(){
	if(running){
		if(!playing){
			if(!paused){
				Mix_FadeInMusic(music[current], 0, FADEIN_DELAY);
				playing = true;
			}
			else {
				Mix_ResumeMusic();
				paused = false;
			}
		}
	}
	else
		fprintf(stderr, "music_t::play: No se puede iniciar la reproducción de música porque no hay una lista cargada.\n");
}

/**
 * @brief La música se pausa si se está reproduciendo.
 */
void music_t::pause(){
	if(running && playing && !paused){
		Mix_PauseMusic();
		paused = true;
	}
}

/**
 * @brief La pista actual se para de reproducir (No pasa automáticamente a la siguiente pista).
 * @see nextTrack
 */
void music_t::halt(){
	if(running && playing){
		Mix_HaltMusic();
		playing = false;
		paused = false;
	}
}

/**
 * @brief Le asigna un volumen a la música que se está reproduciendo.
 * @param vol Valor del volumen que se le va a asignar, perteneciente al intervalo (0, 128).
 * 0 se corresponde con silencioso y 128 es el volumen máximo.
 */
void music_t::setVol(int vol){
	if(vol != volume && vol >= 0 && vol <= MAX_VOLUME)
		Mix_VolumeMusic(vol);
}

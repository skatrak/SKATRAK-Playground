#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "../include/sfx.hpp"

/**
 * @brief Constructor. Inicializa el volumen a DEFAULT_SFX_VOLUME
 */
sfx_t::sfx_t(): sound(NULL), volume(DEFAULT_SFX_VOLUME)
{
}

/**
 * @brief Constructor. Inicializa el volumen a DEFAULT_SFX_VOLUME y abre un archivo de sonido.
 * @param filename Ruta al archivo de sonido que se desea cargar.
 * @see setSound
 */
sfx_t::sfx_t(string filename): sound(NULL), volume(DEFAULT_SFX_VOLUME) {
	setSound(filename);
}

/**
 * @brief Destructor. Libera la memoria ocupada por el archivo de sonido si fue cargado.
 */
sfx_t::~sfx_t(){
	if(sound != NULL)
		Mix_FreeChunk(sound);
}

/**
 * @brief Carga en memoria un archivo de sonido.
 * @param filename Nombre del fichero que se desea cargar.
 */
void sfx_t::setSound(string filename){
	if(sound != NULL){
		Mix_FreeChunk(sound);
		sound = NULL;
	}
	sound = Mix_LoadWAV(filename.c_str());
	if(sound == NULL)
		fprintf(stderr, "No se ha podido cargar el sonido \"%s\"", filename.c_str());
}

/**
 * @brief Cambia el volumen de reproducción del sonido.
 * @param vol Valor del nuevo volumen que se desea asignar entre 0 y 128.
 */
void sfx_t::setVol(int vol){
	if(vol >= 0 && vol <= 128)
		Mix_VolumeChunk(sound, vol);
	else
		Mix_VolumeChunk(sound, DEFAULT_SFX_VOLUME);
}

/**
 * @brief Reproduce el efecto de sonido una vez si se ha cargado
 */
void sfx_t::play(){
	if(sound != NULL){
		Mix_PlayChannel(-1, sound, 0);
	}
}

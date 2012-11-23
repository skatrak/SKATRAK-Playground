#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "../include/sfx.hpp"

sfx_t::sfx_t(): sound(NULL), volume(DEFAULT_SFX_VOLUME)
{
}

sfx_t::sfx_t(string filename): sound(NULL), volume(DEFAULT_SFX_VOLUME) {
	setSound(filename);
}

sfx_t::~sfx_t(){
	if(sound != NULL)
		Mix_FreeChunk(sound);
}

void sfx_t::setSound(string filename){
	if(sound != NULL){
		Mix_FreeChunk(sound);
		sound = NULL;
	}
	sound = Mix_LoadWAV(filename.c_str());
	if(sound == NULL)
		fprintf(stderr, "No se ha podido cargar el sonido \"%s\"", filename.c_str());
}

void sfx_t::setVol(int vol){
	if(vol >= 0 && vol <= 128)
		Mix_VolumeChunk(sound, vol);
	else
		Mix_VolumeChunk(sound, DEFAULT_SFX_VOLUME);
}

void sfx_t::play(){
	if(sound != NULL){
		Mix_PlayChannel(-1, sound, 0);
	}
}

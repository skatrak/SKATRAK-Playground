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

#include "../include/SKATRAK_PLAYGROUND.hpp"

/**
 * @brief Constructor. Inicializa el volumen a DEFAULT_SFX_VOLUME
 */
sfx_t::sfx_t(): sound(NULL), volume(DEFAULT_SFX_VOLUME)
{
}

/**
 * @brief Constructor. Inicializa el volumen a DEFAULT_SFX_VOLUME y abre un archivo de sonido.
 * @param path Ruta al archivo de sonido que se desea cargar.
 * @see setSound
 */
sfx_t::sfx_t(string path): sound(NULL), volume(DEFAULT_SFX_VOLUME) {
	setSound(path);
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
 * @param path Nombre del fichero que se desea cargar.
 */
void sfx_t::setSound(string path){
	string compPath = SFX_PATH;
	compPath += path;

	if(sound != NULL){
		Mix_FreeChunk(sound);
		sound = NULL;
	}
	sound = Mix_LoadWAV(compPath.c_str());
	if(sound == NULL)
		fprintf(stderr, "No se ha podido cargar el sonido \"%s\"", compPath.c_str());
}

/**
 * @brief Cambia el volumen de reproducción del sonido.
 * @param vol Valor del nuevo volumen que se desea asignar entre 0 y 128.
 */
void sfx_t::setVol(int vol){
	if(vol >= 0 && vol <= MAX_VOLUME)
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

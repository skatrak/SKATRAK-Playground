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
#include "system.hpp"
// Estándar
#include <string>
using std::string;
// SDL
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
// Propias
#include "SKATRAK_PLAYGROUND.hpp"
#include "music.hpp"

/**
 * @brief Crea la clase sistema e inicializa las propiedades de la pantalla. También inicializa SDL.
 * @param scr_w Anchura de la pantalla.
 * @param scr_h Altura de la pantalla.
 * @param depth Profundidad de bits de la pantalla.
 * @note En el caso de que la pantalla no se pudiera iniciar con las opciones especificadas, imprimirá un mensaje de error.
 */
system_t::system_t(int scr_w, int scr_h, int depth): screen(NULL), wIcon(NULL), substInit(0), screenWidth(scr_w), screenHeight(scr_h), bpp(depth), fullscr(true) {
	if(initSubsystems(SYS_SUBST_SDL)){
		screen = SDL_SetVideoMode(screenWidth, screenHeight, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
		if(screen == NULL)
			fprintf(stderr, "system_t::system_t: No se ha podido iniciar el modo de video %dx%d a %d bits: %s.\n", screenWidth, screenHeight, bpp, SDL_GetError());
		SDL_WM_SetCaption("SKATRAK Playground", NULL);
	}
}

/**
 * @brief Destructor. Libera la memoria ocupada por la pantalla y cierra SDL.
 */
system_t::~system_t(){
	if(wIcon != NULL)
		SDL_FreeSurface(wIcon);
	if(screen != NULL){
		SDL_FreeSurface(screen);
		screen = NULL;
	}
	quitSubsystems(SYS_SUBST_ALL);
}

/**
 * @brief Inicializar las librerías de SDL especificadas.
 * @param flags Máscara de bits especificando las librerías a inicializar.
 * @return Librerías que están inicializadas tras la llamada.
 * @note No utilizar las funciones de SDL directamente, porque entonces el sistema
 * no sabría qué es lo que tiene que cerrar antes de salir.
 */
unsigned int system_t::initSubsystems(unsigned int flags){
	// Si ya lo hemos iniciado todo, evitamos tener que comprobarlo uno por uno
	if((substInit & flags) == flags) return substInit;

	if(flags & SYS_SUBST_SDL){
		if(!SDL_WasInit(SDL_INIT_EVERYTHING) && SDL_Init(SDL_INIT_EVERYTHING) < 0)
			fprintf(stderr, "system_t::initSubsystems: No se ha podido inicializar SDL: %s.\n", SDL_GetError());
		else
			substInit |= SYS_SUBST_SDL;
	}
	if(flags & SYS_SUBST_MIX){
		if(!Mix_QuerySpec(NULL, NULL, NULL) && Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096))
			fprintf(stderr, "system_t::initSubsystems: No se ha podido inicializar SDL_mixer: %s.\n", Mix_GetError());
		else {
			Mix_AllocateChannels(AUDIO_CHANNELS);
			substInit |= SYS_SUBST_MIX;
		}
	}
	if(flags & SYS_SUBST_TTF){
		if(!TTF_WasInit() && TTF_Init() < 0)
			fprintf(stderr, "system_t::initSubsystems: No se ha podido inicializar SDL_TTF: %s.\n", TTF_GetError());
		else
			substInit |= SYS_SUBST_TTF;
	}
	return substInit;
}

/**
 * @brief Cerrar las librerías de SDL especificadas.
 * @param flags Máscara de bits especificando las librerías a cerrar.
 */
void system_t::quitSubsystems(unsigned int flags){
	// Si no hemos iniciado lo que nos piden, salimos sin perder tiempo
	if(!(substInit & flags)) return;

	if(flags & SYS_SUBST_TTF){
		printf("Cerrando SDL_TTF...\n");
		TTF_Quit();
		flags &= ~SYS_SUBST_TTF;
	}
	if(flags & SYS_SUBST_MIX){
		printf("Cerrando SDL_Mixer...\n");
		Mix_CloseAudio();
		flags &= ~SYS_SUBST_MIX;
	}
	if(flags & SYS_SUBST_SDL){
		printf("Cerrando SDL...\n");
		SDL_Quit();
		flags &= ~SYS_SUBST_SDL;
	}
}

/**
 * @brief Intercambia entre pantalla completa y ventana.
 */
void system_t::toggleFullscreen(){
	fullscr? fullscr = false : fullscr = true;
	if(screen != NULL){
		SDL_FreeSurface(screen);
		screen = NULL;
	}
	if(fullscr){
		screen = SDL_SetVideoMode(screenWidth, screenHeight, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
		if(screen == NULL)
			fprintf(stderr, "system_t::toggleFullscreen: No se ha podido iniciar el modo de video %dx%d a %d bits con pantalla completa: %s.\n", screenWidth, screenHeight, bpp, SDL_GetError());
	} else {
		screen = SDL_SetVideoMode(screenWidth, screenHeight, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);
		if(screen == NULL)
			fprintf(stderr, "system_t::toggleFullscreen: No se ha podido iniciar el modo de video %dx%d a %d bits sin pantalla completa: %s.\n", screenWidth, screenHeight, bpp, SDL_GetError());
	}
}

/**
 * @brief Le da un icono a la ventana del programa.
 * @param iconpath Ruta del icono.
 * @note Este icono no será visible en pantalla completa.
 */
void system_t::setIcon(string iconpath){
	string compPath = IMG_PATH;
	compPath += iconpath;

	if(wIcon != NULL){
		SDL_FreeSurface(wIcon);
		wIcon = NULL;
	}
	wIcon = IMG_Load(compPath.c_str());
	if(wIcon == NULL)
		fprintf(stderr, "system_t::setIcon: No se ha podido cargar el icono del programa: %s.\n", SDL_GetError());
	else
		SDL_WM_SetIcon(wIcon, NULL);
}

/**
 * @brief Actualiza la pantalla.
 * @note Es necesario llamar esta función para que se intercambien los buffers de vídeo.
 */
void system_t::update(){
	if(screen != NULL)
		SDL_Flip(screen);
	else
		fprintf(stderr, "system_t::update: No se ha podido mostrar la pantalla.\n");
}

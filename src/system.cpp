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

/**
 * @brief Crea la clase sistema e inicializa las propiedades de la pantalla. También inicializa SDL.
 * @param scr_w Anchura de la pantalla.
 * @param scr_h Altura de la pantalla.
 * @param depth Profundidad de bits de la pantalla.
 * @note En el caso de que la pantalla no se pudiera iniciar con las opciones especificadas, imprimirá un mensaje de error.
 */
system_t::system_t(int scr_w, int scr_h, int depth): screen(NULL), wIcon(NULL), screenWidth(scr_w), screenHeight(scr_h), bpp(depth), fullscr(true) {
	if(!SDL_WasInit(SDL_INIT_EVERYTHING) && SDL_Init(SDL_INIT_EVERYTHING) < 0)
		fprintf(stderr, "No se ha podido inicializar SDL: %s.\n", SDL_GetError());
	screen = SDL_SetVideoMode(screenWidth, screenHeight, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	if(screen == NULL)
		fprintf(stderr, "No se ha podido iniciar el modo de video %dx%d a %d bits: %s.\n", screenWidth, screenHeight, bpp, SDL_GetError());
	SDL_WM_SetCaption("SKATRAK Playground", NULL);
}

/**
 * @brief Destructor. Libera la memoria ocupada por la pantalla y cierra SDL.
 */
system_t::~system_t(){
	if(screen != NULL)
		SDL_FreeSurface(screen);
	SDL_Quit();
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
			fprintf(stderr, "No se ha podido iniciar el modo de video %dx%d a %d bits con pantalla completa: %s.\n", screenWidth, screenHeight, bpp, SDL_GetError());
	} else {
		screen = SDL_SetVideoMode(screenWidth, screenHeight, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);
		if(screen == NULL)
			fprintf(stderr, "No se ha podido iniciar el modo de video %dx%d a %d bits sin pantalla completa: %s.\n", screenWidth, screenHeight, bpp, SDL_GetError());
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
		fprintf(stderr, "No se ha podido cargar el icono del programa: %s.\n", SDL_GetError());
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
		fprintf(stderr, "No se ha podido mostrar la pantalla.\n");
}

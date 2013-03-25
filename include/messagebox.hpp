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

#ifndef __MESSAGEBOX_HPP__
#define __MESSAGEBOX_HPP__

/* Inclusión de cabeceras necesarias */
// Estándar
#include <string>
using std::string;
// SDL
#include "SDL/SDL.h"

/* Declaración adelantada de structs/clases que no se utilizan directamente */
class font_t;
class image_t;

/**
 * @class messagebox_t
 * @brief Crea un cuadro de mensaje con una cierta cantidad de posibles respuestas entre 1 y 4.
 */
class messagebox_t {
	private:
		int nOpt, selIndex;
		font_t** text;
		image_t* box;
		SDL_Rect marker, *msgPos;
		SDL_Rect wndPos;
	public:
		messagebox_t(void);
		messagebox_t(int optNumber);
		~messagebox_t(void);
		void setOpts(int optNumber);
		void setFont(string fontName, int fontSize);
		void setFont(font_t* fontStyle);
		void setText(int index, string fontText);
		void setBackground(string path);
		int locateTexts(void);
		int loop(SDL_Surface* screen);
};

#endif

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

#ifndef __MENU_T__
#define __MENU_T__

/* Definición de los flags para alinear los menús */
#define MENU_ALIGN_RIGHT	0x00000001
#define MENU_ALIGN_LEFT		0x00000002
#define MENU_ALIGN_UP		0x00000004
#define MENU_ALIGN_DOWN		0x00000008

/* Definición de los márgenes de la pantalla */
const int MENU_MARGIN_H = 64;
const int MENU_MARGIN_V = 32;
const int MENU_OPT_MARGIN = 32;

/* Definición de las funciones de callback: Reciben un puntero a algún dato o estructura que quieras y devuelven hasta dónde se retrocederá en la jerarquía de menús */
typedef returnVal (*MenuCallbackFunc)(void*);

/**
 * @class menu_t
 * @brief Clase encargada de representar un menú y gestionar los eventos cuando estamos en uno
 */
class menu_t {
	private:
		int nOpt;					// Número de elementos en el menú
		int selIndex;				// Índice del elemento del menú seleccionado
		SDL_Rect* textPos;			// Array de posiciones de textos
		font_t** optName;			// Array de punteros a textos de opciones
		image_t* selImage;			// Imagen debajo de la opción seleccionada
		image_t* backImage;			// Imagen de fondo
		sfx_t* clickSound;			// Sonido al pulsar un botón
		sfx_t* selectSound;			// Sonido al cambiar de selección
		MenuCallbackFunc* callback; // Array de callbacks (Uno por cada opción)
	public:
		menu_t(void);
		menu_t(int optNumber);
		~menu_t(void);
		void setOpts(int optNumber);
		void setOpt(int index, MenuCallbackFunc func);
		void setTexts(string fontName, int fontSize);
		void setTexts(font_t* fontStyle);
		void setText(int index, string text);
		void setBackground(string imageName);
		void setImage(string imageName);
		void setClickSFX(string soundName);
		void setSelectSFX(string soundName);
		void align(unsigned int flags);
		returnVal update(SDL_Event* event);
		void blit(SDL_Surface* screen);
};

#endif

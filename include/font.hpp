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

#ifndef __FONT_T__
#define __FONT_T__

const int DEFAULT_FONT_SIZE = 24;
const int DEFAULT_FONT_STYLE = TTF_STYLE_NORMAL;

/**
 * @class font_t
 * @brief Clase que representa una fuente True-Type que se puede imprimir gráficamente por pantalla.
 */
class font_t {
	private:
		TTF_Font* font;
		SDL_Surface* rendered;
		string fontName;
		int fontSize;
		int fontStyle;
		string fontText;
		SDL_Color fontColor;
		int fontAlpha;
		bool changed;
	public:
		font_t(void);
		font_t(font_t& copy);
		font_t(string path);
		~font_t(void);
		void open(string path);
		void setSize(int size);
		void setStyle(int style);
		void setText(string text);
		void setColor(int R, int G, int B);
		void setAlpha(int alpha);
		void blit(int x, int y, SDL_Surface* screen);
		int width(void);
		int height(void);
		int size(void){ return fontSize; }
};

/**
 * @fn font_t::size
 * @return Valor del tamaño de la fuente.
 */

#endif

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

#ifndef __SYSTEM_T__
#define __SYSTEM_T__

/* Flags para especificar subsistemas a inicializar o cerrar */
#define SYS_SUBST_ALL 0x0000000F
#define SYS_SUBST_SDL 0x00000001
#define SYS_SUBST_MIX 0x00000002
#define SYS_SUBST_TTF 0x00000004
//#define SUBST_NET 0x00000008 En caso de que añada funciones de comunicación en LAN

/**
 * @class system_t
 * @brief Representa todo lo necesario para inicializar y cerrar SDL.
 * @note Sólo se puede tener un objeto de este tipo al mismo tiempo en un programa.
 */
class system_t {
	private:
		SDL_Surface* screen;
		SDL_Surface* wIcon;
		unsigned int substInit;
		int screenWidth;
		int screenHeight;
		int bpp;
		bool fullscr;
	public:
		system_t(int scr_w, int scr_h, int depth);
		~system_t(void);
		unsigned int initSubsystems(unsigned int flags);
		void quitSubsystems(unsigned int flags);
		void toggleFullscreen(void);
		void setIcon(string iconpath);
		int width(void){ return screenWidth; }
		int height(void){ return screenHeight; }
		SDL_Surface* scr(void){ return screen; }
		void update(void);
};

/**
 * @fn system_t::width
 * @return Devuelve la anchura de la pantalla creada por SDL.
 */

/**
 * @fn system_t::height
 * @return Devuelve la altura de la pantalla creada por SDL.
 */

/**
 * @fn system_t::scr
 * @return Devuelve un puntero a la SDL_Surface que apunta a la pantalla de SDL.
 */

#endif

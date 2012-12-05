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

#ifndef __TIMEKEEPER_T__
#define __TIMEKEEPER_T__

/**
 * @class timekeeper_t
 * @brief Temporizador para controlar la velocidad de ejecución del programa y la cantidad de fotogramas que se van renderizando.
 */
class timekeeper_t {
	private:
		int start;
		int current;
		int frames;
	public:
		timekeeper_t(): current(0), frames(0) { start = SDL_GetTicks(); }
		void refresh();
		int elapsed();
		void waitFramerate(int fps);
		int renderedFrames();
};

/**
 * @fn timekeeper_t::timekeeper_t
 * @brief Constructor. Inicializa el reloj con el tiempo inicial.
 */

#endif


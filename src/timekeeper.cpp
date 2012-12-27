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
 * @brief Actualiza el contador de tiempo.
 */
void timekeeper_t::refresh(){
	current = SDL_GetTicks();
}

/**
 * @return Tiempo transcurrido en milisegundos desde que se creó el contador.
 */
int timekeeper_t::elapsed(){
	return SDL_GetTicks() - start;
}

/**
 * @brief Espera el tiempo necesario para controlar la velocidad a la que funciona el juego.
 * @note Esta función aumenta el número de frames que se supone que se han mostrado por pantalla.
 *
 * Es recomendable llamar a esta función al final del game loop y llamar a timekeeper_t::refresh al principio del mismo.
 * Así conseguimos que el juego funcione a la misma velocidad en cualquier máquina.
 */
void timekeeper_t::waitFramerate(int fps){
	if(fps > 0){
		unsigned int tmp = (unsigned int)1000/fps;
		if(SDL_GetTicks() - current < tmp)
			SDL_Delay(tmp - (SDL_GetTicks() - current));
	}
	frames++;
}

/**
 * @return Número de fotogramas que se han imprimido por pantalla desde la última vez que se llamó.
 * @note Esta función resetea el número de fotogramas que se han imprimido por pantalla.
 * @see timekeeper_t::waitFramerate
 */
int timekeeper_t::renderedFrames(){
	int tmp = frames;
	frames = 0;
	return tmp;
}

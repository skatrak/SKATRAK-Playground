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

#ifndef __SFX_T__
#define __SFX_T__

/* Inclusión de cabeceras necesarias */
// Estándar
#include <string>
using std::string;
// SDL
#include "SDL/SDL_mixer.h"

/* Constantes */
const int DEFAULT_SFX_VOLUME = 128;

/**
 * @class sfx_t
 * @brief Representa un efecto de sonido, que se reproduce una sola vez cuando se le indica.
 * @note Como la clase music_t ya inicializa SDL, no hay que hacerlo para cada efecto de sonido.
 * Suponemos que hay una cantidad suficiente de canales de audio reservados.
 */
class sfx_t {
	private:
		Mix_Chunk* sound;
		int volume;
	public:
		sfx_t(void);
		sfx_t(string path);
		~sfx_t(void);
		void setSound(string path);
		void setVol(int vol);
		void play(void);
		int vol(void){ return volume; }
};

/**
 * @fn sfx_t::vol
 * @return Volumen actual del efecto de sonido.
 */

#endif

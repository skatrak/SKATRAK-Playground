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

#ifndef __TABLERO_T__
#define __TABLERO_T__

// Diferentes contenidos que puede tener una celda del tablero
enum CellState {
	CELL_P1,
	CELL_P2,
	CELL_EMPTY
};

// Diferentes resultados que pueden haber en una partida de Conecta 4
enum ResultConecta4 {
	P1_WINS,
	P2_WINS,
	NOT_FINISHED,
	NOBODY_WINS
};

// Separación entre agujeros en el tablero y separación de los agujeros y los bordes
const int FICHA_OFFSET_X = 40;
const int FICHA_OFFSET_Y = 16;

/**
 * @class tablero_t
 * @brief Clase para representar el tablero donde se juega al Conecta 4.
 */
class tablero_t {
	private:
		SDL_Rect posicion;
		int jugador, columna;
		CellState** tablero;
		image_t* img_tab;
		image_t* sig[2];
		image_t* ficha[2];
		sfx_t* choque;
	protected:
		void creaTab(void);
		void destruyeTab(void);
		void soltarFicha(void);
	public:
		tablero_t(void);
		tablero_t(int posx, int posy);
		~tablero_t(void);
		void setPos(int posx, int posy);
		void setTab(string path);
		void setMark(int player, string path);
		void setFich(int player, string path);
		void setSFX(string path);
		void setPlayer(int player);
		int width(void);
		int height(void);
		int posX(void){ return posicion.x; }
		int posY(void){ return posicion.y; }
		int actualPlayer(void){ return jugador; }
		bool isEmpty(void);
		void reset(void);
		void update(SDL_Event* event);
		void blit(SDL_Surface* screen);
		ResultConecta4 checkWin(void);
};

/**
 * @fn tablero_t::posX
 * @brief Devuelve la posición en el eje x del tablero.
 * @return Posición en el eje x del tablero.
 */

/**
 * @fn tablero_t::posY
 * @brief Devuelve la posición en el eje y del tablero.
 * @return Posición en el eje y del tablero.
 */

/**
 * @fn tablero_t::actualPlayer
 * @brief Devuelve el jugador del cual es el turno ahora.
 * @return Un 0 si es el jugador 1 o un 1 si es el jugador 2.
 */

#endif

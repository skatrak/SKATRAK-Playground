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

#ifndef __SNAKEPIECE_T__
#define __SNAKEPIECE_T__

// Direcciones de movimiento de la serpiente
enum Direction {
	MOVE_UP = 0,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};

/* Diferentes partes de la serpiente */
enum SnakePart {
	SNAKE_HEAD = 0,
	SNAKE_BODY,
	SNAKE_TAIL
};

/**
 * @class snakePiece_t
 * @brief Representa un elemento para una lista doblemente enlazada de 'eslabones' de la serpiente.
 */
class snakePiece_t {
	private:
		int x, y;
		int tilePos;	// Contiene el índice horizontal (el que depende de la dirección de movimiento) del tile
	public:
		/// Puntero al siguiente elemento de la lista.
		snakePiece_t* next;
		/// Puntero al elemento anterior de la lista.
		snakePiece_t* prev;
	public:
		snakePiece_t(void);
		snakePiece_t(int posX, int posY, snakePiece_t* prevPiece = NULL);
		snakePiece_t(snakePiece_t* copy, snakePiece_t* prevPiece = NULL);
		~snakePiece_t(void){}
		int posX(void){ return x; }
		int posY(void){ return y; }
		int tilePosX(void){ return tilePos; }
		void setPos(int posX, int posY);
		void setTilePos(int posX);
		void move(Direction direction);
		void blit(SDL_Surface* screen, int posX, int posY, SnakePart part, image_t* tiles, int tileSize);
};

/**
 * @fn snakePiece_t::~snakePiece_t
 * @brief Destructor.
 */

/**
 * @fn snakePiece_t::posX
 * @brief Devuelve la posición en el eje X actual del eslabón.
 * @return Posición en el eje X.
 */

/**
 * @fn snakePiece_t::posY
 * @brief Devuelve la posición en el eje Y actual del eslabón.
 * @return Posición en el eje Y.
 */

/**
 * @fn snakePiece_t::tilePosX
 * @brief Devuelve el índice en el eje X del tile que le corresponde al eslabón.
 * @return Índice en el eje X del tile en la imagen.
 */

#endif

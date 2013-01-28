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

#ifndef __SNAKE_T__
#define __SNAKE_T__

// Número por defecto de eslabones de la serpiente
const int SNAKE_DEFAULT_PIECES = 5;

/**
 * @class snake_t
 * @brief Representa a una serpiente del juego. Es una lista doblemente enlazada de snakePiece_t.
 */
class snake_t {
	private:
		int pieceCount;
		Direction direction;
		snakePiece_t* head;		// Para recorrer la lista
		snakePiece_t* tail;		// Para recorrer la lista de forma inversa o añadir rápidamente más elementos
	public:
		snake_t(int pieces = SNAKE_DEFAULT_PIECES);
		~snake_t(void);
		void setPos(int posX, int posY, Direction newDirection);
		int headPos(int* x, int* y);
		void step(void);
		void addPiece(int nPieces = 1);
		bool checkCollision(void);
};

#endif

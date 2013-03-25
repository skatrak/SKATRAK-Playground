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

/* Inclusión de cabeceras necesarias */
#include <string>
using std::string;

/* Declaración adelantada de structs/clases que no se utilizan directamente */
struct SDL_Surface;
class image_t;
class snakePiece_t;
enum Direction;

/* Constantes */
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
		image_t* snake;			// Fichero de tiles con las posiciones de la serpiente
		int tileSize;			// Tamaño de cada segmento de la serpiente (son cuadrados)
		bool turned;			// Especifica si en este fotograma ya se ha hecho un giro
	protected:
		int getHeadTilePos(void);
	public:
		snake_t(int pieces = SNAKE_DEFAULT_PIECES);
		~snake_t(void);
		void setPos(int posX, int posY, Direction newDirection);
		void setImg(string path, int newTileSize);
		int headPos(int* x, int* y);
		void setHeadPos(int x, int y);
		void turn(Direction newDirection);
		void step(void);
		void addPiece(int nPieces = 1);
		bool checkCollision(int posX = -1, int posY = -1);
		void blit(int x, int y, SDL_Surface* screen);
};

#endif

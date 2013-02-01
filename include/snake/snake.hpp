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

/* Número por defecto de eslabones de la serpiente */
const int SNAKE_DEFAULT_PIECES = 5;

/* Diferentes partes de la serpiente */
enum SnakePart {
	SNAKE_HEAD = 0,
	SNAKE_BODY,
	SNAKE_TAIL
};

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
	protected:
		void getTilePos(SDL_Rect* tilePos, snakePiece_t* next, snakePiece_t* prev, snakePiece_t* actual);
		int getTilePosX(int nPosX, int nPosY, int pPosX, int pPosY, int aPosX, int aPosY);
		int getTilePosY(SnakePart part);
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
		bool checkCollision(void);
		void blit(SDL_Surface* screen, int x, int y);
};

#endif

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

/* Inclusión de cabeceras necesarias */
// Cabecera de la clase
#include "snake/snakePiece.hpp"
// SDL
#include "SDL/SDL.h"
// Propias
#include "image.hpp"

/**
 * @brief Constructor por defecto. Inicializa las variables de la clase con un valor conocido.
 */
snakePiece_t::snakePiece_t(): x(-1), y(-1), tilePos(-1), next(NULL), prev(NULL)
{
}

/**
 * @brief Constructor. Inicializa la posición del eslabón.
 * @param posX Posición del eslabón en el eje X.
 * @param posY Posición del eslabón en el eje Y.
 * @param prevPiece (OPCIONAL) Puntero al elemento anterior de la lista.
 */
snakePiece_t::snakePiece_t(int posX, int posY, snakePiece_t* prevPiece): x(posX), y(posY), tilePos(-1), next(NULL), prev(prevPiece)
{
}

/**
 * @brief Constructor de copia.
 * @param copy Referencia al objeto snakePiece_t al que copiar.
 * @param prevPiece (OPCIONAL) Puntero al elemento anterior de la lista.
 */
snakePiece_t::snakePiece_t(snakePiece_t* copy, snakePiece_t* prevPiece): x(copy->x), y(copy->y), tilePos(copy->tilePos), next(NULL), prev(prevPiece)
{
}

/**
 * @brief Sitúa el eslabón en una posición.
 * @param posX Posición del eslabón en el eje X.
 * @param posY Posición del eslabón en el eje Y.
 */
void snakePiece_t::setPos(int posX, int posY){
	x = posX;
	y = posY;
}

/**
 * @brief Establece el índice en el eje X del tile correspondiente a este eslabón en la imagen.
 * @param posX Índice en el eje X.
 */
void snakePiece_t::setTilePos(int posX){
	tilePos = posX;
}

/**
 * @brief Mueve el eslabón una posición hacia una dirección.
 * @param direction Dirección hacia la que mover el eslabón
 */
void snakePiece_t::move(Direction direction){
	switch(direction){
	case MOVE_UP:
		y--;
		break;
	case MOVE_DOWN:
		y++;
		break;
	case MOVE_LEFT:
		x--;
		break;
	case MOVE_RIGHT:
		x++;
		break;
	}
}

/**
 * @brief Imprime el eslabón de la serpiente por pantalla.
 * @param screen Superficie sobre la que realizar el blitting.
 * @param posX Posición en el eje X de comienzo de la zona de movimiento de la serpiente en pantalla.
 * @param posY Posición en el eje Y de comienzo de la zona de movimiento de la serpiente en pantalla.
 * @param part Parte de la serpiente a la que corresponde este segmento.
 * @param tiles Imagen de tiles.
 * @param tileSize Tamaño de la imagen en pantalla.
 */
void snakePiece_t::blit(SDL_Surface* screen, int posX, int posY, SnakePart part, image_t* tiles, int tileSize){
	SDL_Rect zone = {(Sint16)(tilePos * tileSize), (Sint16)(part * tileSize), (Uint16)tileSize, (Uint16)tileSize};
	tiles->blit((x*tileSize) + posX, (y*tileSize) + posY, screen, &zone);
}

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
#include <snake/snakePiece.hpp>
#include <snake/snake.hpp>

/**
 * @brief Devuelve la posición y tamaño que le corresponde al tile en la imagen sabiendo cuál es el siguiente y el anterior.
 * @param tilePos (SALIDA) Puntero a una estructura ya reservada en memoria donde guardar el resultado.
 * @param next Puntero al siguiente elemento en la lista.
 * @param prev Puntero al elemento anterior de la lista.
 * @param actual Puntero al elemento actual de la lista.
 */
void snake_t::getTilePos(SDL_Rect* tilePos, snakePiece_t* next, snakePiece_t* prev, snakePiece_t* actual){
	if(tilePos == NULL || head == NULL || actual == NULL) return;

	// Es la cabeza
	if(prev == NULL){
		switch(direction){
		case MOVE_UP:
			tilePos->x = getTilePosX(next->posX(), next->posY(), actual->posX(), actual->posY()-1, actual->posX(), actual->posY());
			break;
		case MOVE_DOWN:
			tilePos->x = getTilePosX(next->posX(), next->posY(), actual->posX(), actual->posY()+1, actual->posX(), actual->posY());
			break;
		case MOVE_LEFT:
			tilePos->x = getTilePosX(next->posX(), next->posY(), actual->posX()-1, actual->posY(), actual->posX(), actual->posY());
			break;
		case MOVE_RIGHT:
			tilePos->x = getTilePosX(next->posX(), next->posY(), actual->posX()+1, actual->posY(), actual->posX(), actual->posY());
			break;
		}
		tilePos->y = getTilePosY(SNAKE_HEAD);
		tilePos->w = tilePos->h = tileSize;
	}
	// Es la cola
	else if(next == NULL){
		tilePos->x = getTilePosX(-1, -1, prev->posX(), prev->posY(), actual->posX(), actual->posY());
		tilePos->y = getTilePosY(SNAKE_TAIL);
		tilePos->w = tilePos->h = tileSize;
	}
	// Cuerpo
	else {
		tilePos->x = getTilePosX(next->posX(), next->posY(), prev->posX(), prev->posY(), actual->posX(), actual->posY());
		tilePos->y = getTilePosY(SNAKE_BODY);
		tilePos->w = tilePos->h = tileSize;
	}
}

/**
 * @brief Devuelve la posición en el eje X del tile.
 * @param nPosX Posición en el eje X del siguiente elemento.
 * @param nPosY Posición en el eje Y del siguiente elemento.
 * @param pPosX Posición en el eje X del elemento anterior.
 * @param pPosY Posición en el eje Y del elemento anterior.
 * @param aPosX Posición en el eje X del elemento actual.
 * @param aPosY Posición en el eje Y del elemento actual.
 * @return Posición en el eje X del tile o -1 en caso de error.
 */
int snake_t::getTilePosX(int nPosX, int nPosY, int pPosX, int pPosY, int aPosX, int aPosY){
	if(nPosX == -1 || nPosY == -1){
		if(aPosX > pPosX)
			return 6*tileSize;
		else if(aPosX < pPosX)
			return 9*tileSize;
		else if(aPosY > pPosY)
			return 0;
		else if(aPosY < pPosY)
			return 3*tileSize;
	}

	int relX = pPosX - nPosX;
	int relY = pPosY - nPosY;

	switch(relX){
	case 0:
		if(relY == -2)
			return 0;
		else if(relY == 2)
			return 3*tileSize;
		// Hay un corte vertical
		else {
			if(relY > 0)
				return 0;
			else
				return 3*tileSize;
		}
	case -1:
		if(relY == -1){
			if(aPosX == pPosX)
				return 7*tileSize;
			else if(aPosY == pPosY)
				return tileSize;
		}
		else if(relY == 1){
			if(aPosX == pPosX)
				return 8*tileSize;
			else if(aPosY == pPosY)
				return 4*tileSize;
		}
		// Hay un corte vertical
		else {
			if(relY > 0)
				return 11*tileSize;
			else
				return 8*tileSize;
		}
		break;
	case 1:
		if(relY == -1){
			if(aPosX == pPosX)
				return 10*tileSize;
			else if(aPosY == pPosY)
				return 2*tileSize;
		}
		else if(relY == 1){
			if(aPosX == pPosX)
				return 11*tileSize;
			else if(aPosY == pPosY)
				return 5*tileSize;
		}
		// Hay un corte vertical
		else {
			if(relY > 0)
				return 8*tileSize;
			else
				return 11*tileSize;
		}
		break;
	case -2:
		return 6*tileSize;
	case 2:
		return 9*tileSize;
	// Hay un corte horizontal
	default:
		if(relX > 0){
			if(relY == 1)
				return 8*tileSize;
			else if(relY == -1)
				return 7*tileSize;
			else
				return 6*tileSize;
		}
		else {
			if(relY == 1)
				return 11*tileSize;
			else if(relY == -1)
				return 10*tileSize;
			else
				return 9*tileSize;
		}
	}

	// No se debería llegar hasta aquí
	return -1;
}

/**
 * @brief Devuelve la posición en el eje Y del tile.
 * @param part Parte de la serpiente a la que corresponde el tile.
 * @return Posición en el eje Y del tile.
 */
int snake_t::getTilePosY(SnakePart part){
	return part * tileSize;
}

/**
 * @brief Constructor. Crea la serpiente con el tamaño especificado.
 * @param pieces (OPCIONAL) Número de eslabones que se desea inicialmente.
 */
snake_t::snake_t(int pieces): pieceCount(0), head(NULL), tail(NULL), snake(NULL) {
	addPiece(pieces);
	setPos(0, 0, MOVE_UP);
}

/**
 * @brief Destructor. Borra toda la lista enlazada de eslabones.
 */
snake_t::~snake_t(void){
	for(snakePiece_t* aux = head; aux != NULL; aux = head){
		head = aux->next;
		delete aux;
	}
	if(snake != NULL)
		delete snake;
}

/**
 * @brief Situa los eslabones alineados hacia una dirección con la cabeza en una posición.
 * @param posX Posición de la cabeza en el eje X.
 * @param posY Posición de la cabeza en el eje Y.
 * @param newDirection dirección hacia la que se va a mover la serpiente.
 */
void snake_t::setPos(int posX, int posY, Direction newDirection){
	// Si no hay serpiente no la podemos colocar
	if(head == NULL) return;

	direction = newDirection;
	head->setPos(posX, posY);

	int incX = 0, incY = 0;
	switch(direction){
	case MOVE_UP:
		incY = -1;
		break;
	case MOVE_DOWN:
		incY = 1;
		break;
	case MOVE_LEFT:
		incX = 1;
		break;
	case MOVE_RIGHT:
		incX = -1;
		break;
	}

	for(snakePiece_t* aux = head->next; aux != NULL; aux = aux->next){
		posX += incX;
		posY += incY;
		aux->setPos(posX, posY);
	}
}

/**
 * @brief Abre una imagen que contenga los tiles de la serpiente.
 * @param path Nombre de la imagen.
 * @param newTileSize Tamaño de cada tile en la imagen.
 */
void snake_t::setImg(string path, int newTileSize){
	if(snake != NULL){
		delete snake;
		snake = NULL;
	}

	snake = new image_t(path);
	if(snake != NULL){
		tileSize = newTileSize;
		if((double)(snake->width() / (tileSize*12)) != 1.0)
			fprintf(stderr, "snake_t::setImg: [WARNING] La anchura de la imagen no concuerda con el tamaño de los tiles especificado (¿Faltan tiles?).\n");
		if((double)(snake->height() / (tileSize*3)) != 1.0)
			fprintf(stderr, "snake_t::setImg: [WARNING] La altura de la imagen no concuerda con el tamaño de los tiles especificado (¿Falta la Cabeza/Cuerpo/Cola?).\n");
	}
	else
		fprintf(stderr, "snake_t::setImg: Ha ocurrido un error al cargar la imagen.\n");
}

/**
 * @brief Devuelve la posición actual de la cabeza de la serpiente.
 * @param x Dirección de una posición de memoria ya reservada donde se escribirá la posición en el eje X de la serpiente.
 * @param y Dirección de una posición de memoria ya reservada donde se escribirá la posición en el eje Y de la serpiente.
 * @return -1 en caso de que no haya serpiente y 0 si sí la hay.
 */
int snake_t::headPos(int* x, int* y){
	if(head != NULL){
		if(x != NULL)
			*x = head->posX();
		if(y != NULL)
			*y = head->posY();
		return 0;
	}
	else
		return -1;
}

/**
 * @brief Cambia la posición de la cabeza de la serpiente.
 * @param x Posición en el eje X de la cabeza de la serpiente.
 * @param y Posición en el eje Y de la cabeza de la serpiente.
 *
 * Esta función está pensada para permitir a la serpiente aparecer por otro lado al salir de la zona de juego.
 * No se cambia la posición de ningún otro elemento.
 */
void snake_t::setHeadPos(int x, int y){
	if(head == NULL || x < 0 || y < 0){
		fprintf(stderr, "snake_t::setHeadPos: No se ha podido recolocar la cabeza.\n");
		return;
	}
	head->setPos(x, y);
}

/**
 * @brief Gira la serpiente hacia una nueva dirección.
 * @param newDirection Dirección hacia la que se moverá la serpiente a partir de ahora.
 */
void snake_t::turn(Direction newDirection){
	switch(direction){
	case MOVE_UP:
		if(newDirection != MOVE_DOWN && (head->next == NULL || (head->next->posX() != (head->posX()-1) && head->next->posX() != (head->posX()+1))))
			direction = newDirection;
		break;
	case MOVE_DOWN:
		if(newDirection != MOVE_UP && (head->next == NULL || (head->next->posX() != (head->posX()-1) && head->next->posX() != (head->posX()+1))))
			direction = newDirection;
		break;
	case MOVE_LEFT:
		if(newDirection != MOVE_RIGHT && (head->next == NULL || (head->next->posY() != (head->posY()-1) && head->next->posY() != (head->posY()+1))))
			direction = newDirection;
		break;
	case MOVE_RIGHT:
		if(newDirection != MOVE_LEFT && (head->next == NULL || (head->next->posY() != (head->posY()-1) && head->next->posY() != (head->posY()+1))))
			direction = newDirection;
		break;
	}
}

/**
 * @brief Mueve la serpiente una unidad de espacio.
 * @note No llamar a esta función antes que a snake_t::addPiece.
 *
 * El que sea una lista doblemente enlazada permite que podamos recorrer la serpiente en sentido inverso para actualizar las posiciones.
 */
void snake_t::step(void){
	if(head == NULL) return;

	int posX, posY;

	// Actualizamos todas las posiciones de los eslabones
	for(snakePiece_t* aux = tail; aux->prev != NULL; aux = aux->prev){
		posX = aux->prev->posX();
		posY = aux->prev->posY();
		aux->setPos(posX, posY);
	}

	// Colocamos la cabeza en su nueva posición
	switch(direction){
	case MOVE_UP:
	case MOVE_DOWN:
		posX = head->posX();
		posY = (direction == MOVE_UP)? head->posY() - 1 : head->posY() + 1;
		break;
	case MOVE_LEFT:
	case MOVE_RIGHT:
		posX = (direction == MOVE_LEFT)? head->posX() - 1 : head->posX() + 1;
		posY = head->posY();
		break;
	}
	head->setPos(posX, posY);
}

/**
 * @brief Añade más eslabones a la serpiente.
 * @param nPieces (OPCIONAL) Número de eslabones a añadir.
 */
void snake_t::addPiece(int nPieces){
	pieceCount += nPieces;

	// Iniciamos la serpiente si no lo está ya
	if(tail == NULL){
		head = new snakePiece_t;
		tail = head;
		nPieces--;
	}

	for(int i = 0; i < nPieces; i++){
		tail->next = new snakePiece_t(tail, tail);
		tail = tail->next;
	}
}

/**
 * @brief Detecta si hay colisiones entre la cabeza de la serpiente y cualquier otra parte de la misma.
 * @return true si hay colisión y false si no la hay.
 */
bool snake_t::checkCollision(void){
	if(head == NULL) return false;

	for(snakePiece_t* aux = head->next; aux != NULL; aux = aux->next)
		if(aux->posX() == head->posX() && aux->posY() == head->posY())
			return true;
	return false;
}

/**
 * @brief Imprime toda la serpiente por pantalla.
 * @param screen Superficie sobre la que realizar el blitting.
 * @param x Posición en el eje X de comienzo de la zona de movimiento de la serpiente en la pantalla.
 * @param y Posición en el eje Y de comienzo de la zona de movimiento de la serpiente en la pantalla.
 */
void snake_t::blit(SDL_Surface* screen, int x, int y){
	if(head == NULL || snake == NULL) return;

	SDL_Rect zone;
	for(snakePiece_t* aux = head; aux != NULL; aux = aux->next){
		getTilePos(&zone, aux->next, aux->prev, aux);
		aux->blit(screen, x, y, &zone, snake, tileSize);
	}
}

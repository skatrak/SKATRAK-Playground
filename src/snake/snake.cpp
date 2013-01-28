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
 * @brief Constructor. Crea la serpiente con el tamaño especificado.
 * @param pieces (OPCIONAL) Número de eslabones que se desea inicialmente.
 */
snake_t::snake_t(int pieces): pieceCount(0), head(NULL), tail(NULL) {
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

	int incX, incY;
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
 * @brief Mueve la serpiente una unidad de espacio.
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
		posY = direction == MOVE_UP? head->posY() - 1 : head->posY() + 1;
		break;
	case MOVE_LEFT:
	case MOVE_RIGHT:
		posX = direction == MOVE_LEFT? head->posX() - 1 : head->posX() + 1;
		posY = head->posY();
		break;
	}
}

/**
 * @brief Añade más eslabones a la serpiente.
 * @param (OPCIONAL) Número de eslabones a añadir.
 * @note Llamar a esta función siempre antes de snake_t::step.
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

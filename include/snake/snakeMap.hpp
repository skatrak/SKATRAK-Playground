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

#ifndef __SNAKEMAP_T__
#define __SNAKEMAP_T__

/* Diferentes cosas con las que puede impactar la serpiente en cada movimiento */
enum SnakeHit {
	HIT_NORMAL,	// Se comió una comida
	HIT_BONUS,	// Se comió un bonus
	HIT_WARP,	// Salto de nivel
	HIT_NONE,	// No chocó con nada
	HIT_DEATH	// Se mordió la cola o chocó contra una pared
};

/* Diferentes 'comidas' que pueden aparecer. Al empezar por '0', permiten indexar el tileset de comidas */
enum SnakeFood {
	FOOD_NORMAL = 0,
	FOOD_BONUS,
	FOOD_WARP
};

/**
 * @class snakeMap_t
 * @brief Representa un rectángulo de juego compuesto por la serpiente, bloques opcionales y las comidas y bonus que se puede comer la serpiente.
 *
 * Permite configurar bonus warp para pasar a otro nivel.
 */
class snakeMap_t {
	private:
		struct coord {
			int x, y;
		} mapPos, foodPos, bonusPos, warpPos, *wallPos;
		int nWalls;				// Número de bloques de pared que hay
		image_t* background;	// Define el espacio de juego y le da un aspecto al fondo
		image_t* special;		// Imagen que contiene los tiles de la comida, los bonus, los warps y los muros
		int tileSize;			// Es el mismo para las comidas y los eslabones de la serpiente
		int moveTime;			// Número de fotogramas que tienen que pasar para que se mueva la serpiente
		int foodLimit;			// Número de comidas necesarias para que aparezca un warp
		int timeLimit;			// Número de fotogramas necesarios para que aparezca un warp
		snake_t* snake;			// La serpiente
	protected:
		void locateFood(SnakeFood food);
		bool checkCollision(int posX = -1, int posY = -1);
	public:
		// Constructores y destructor
		snakeMap_t(void);
		snakeMap_t(int posX, int posY);
		snakeMap_t(int posX, int posY, string path);
		~snakeMap_t(void);
		// Opciones del mapa
		void setPos(int posX, int posY);
		void setBackground(string path);
		void loadMapScheme(string path);
		// Imágenes
		void setSnakeImg(string path, int size);
		void setFoodImg(string path);
		// Consulta de atributos
		int width(void) const;
		int height(void) const;
		// Juego
		void setDelay(int delay);
		void setFoodLimit(int nFood){ foodLimit = nFood; }
		void setTimeLimit(int nFrames){ timeLimit = nFrames; }
		void turnSnake(Direction direction);
		SnakeHit update(void);
		void blit(SDL_Surface* screen);
};

/**
 * @fn snakeMap_t::setFoodLimit
 * @brief Establece un número de comidas recogidas antes de que aparezca un warp al siguiente nivel.
 * @param nFood Número de comidas. '-1' Para que sean infinitas.
 */

/**
 * @fn snakeMap_t::setTimeLimit
 * @brief Establece un número de fotogramas antes de que aparezca un warp al siguiente nivel.
 * @param nFrames Número de fotogramas.
 */

#endif

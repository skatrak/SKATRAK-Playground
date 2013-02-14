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
#include <snake/snakeMap.hpp>

/**
 * @brief Constructor por defecto. Inicializa los valores de las variables de la clase.
 */
snakeMap_t::snakeMap_t(): wallPos(NULL), nWalls(0), background(NULL), snakeTiles(NULL), special(NULL), tileSize(-1), moveFreq(1), foodLimit(-1), timeLimit(-1), snake(NULL) {
	snake = new snake_t;
	setPos(0, 0);
}

/**
 * @brief Contructor. Inicializa la clase y coloca el mapa en la pantalla.
 * @param posX Posición en el eje X en la que se colocará el comienzo del mapa en la pantalla.
 * @param posY Posición en el eje Y en la que se colocará el comienzo del mapa en la pantalla.
 */
snakeMap_t::snakeMap_t(int posX, int posY): wallPos(NULL), nWalls(0), background(NULL), snakeTiles(NULL), special(NULL), tileSize(-1), moveFreq(1), foodLimit(-1), timeLimit(-1), snake(NULL) {
	snake = new snake_t;
	setPos(posX, posY);
}

/**
 * @brief Constructor. Inicializa la clase, coloca el mapa en la pantalla y le asigna una imagen de fondo.
 * @param posX Posición en el eje X en la que se colocará el comienzo del mapa en la pantalla.
 * @param posY Posición en el eje Y en la que se colocará el comienzo del mapa en la pantalla.
 * @param path Nombre de la imagen de fondo del mapa.
 */
snakeMap_t::snakeMap_t(int posX, int posY, string path): wallPos(NULL), nWalls(0), background(NULL), snakeTiles(NULL), special(NULL), tileSize(-1), moveFreq(1), foodLimit(-1), timeLimit(-1), snake(NULL) {
	snake = new snake_t;
	setPos(posX, posY);
	setBackground(path);
}

/**
 * @brief Destructor. Libera la memoria asignada a los atributos de la clase.
 */
snakeMap_t::~snakeMap_t(){
	if(wallPos != NULL)
		delete [] wallPos;
	if(background != NULL)
		delete background;
	if(snakeTiles != NULL)
		delete snakeTiles;
	if(special != NULL)
		delete special;
	if(snake != NULL)
		delete snake;
}

/**
 * @brief Coloca el mapa en una posición de la pantalla.
 * @param posX Posición en el eje X en la que se colocará el comienzo del mapa en la pantalla.
 * @param posY Posición en el eje Y en la que se colocará el comienzo del mapa en la pantalla.
 */
void snakeMap_t::setPos(int posX, int posY){
	if(posX < sistema->width() && posX > 0)
		mapPos.x = posX;
	if(posY < sistema->height() && posY > 0)
		mapPos.y = posY;
}

/**
 * @brief Le asigna un fondo al mapa.
 * @param path Nombre de la imagen de fondo.
 * @note Es NECESARIO que un mapa tenga imagen para que funcione. Esto es porque la anchura y la altura del mismo se extraen de la imagen.
 */
void snakeMap_t::setBackground(string path){
	if(background != NULL){
		delete background;
		background = NULL;
	}

	background = new image_t(path);
	if(background == NULL)
		fprintf(stderr, "snakeMap_t::setBackground: No se ha podido cargar la imagen.\n");
}

/**
 * @brief Carga un archivo de texto con un determinado formato para crear un mapa.
 * @param path Nombre del archivo.
 *
 * El formato del archivo será el siguiente: 
 * El símbolo 'X' representará las paredes. 
 * El símbolo 'H' representará la posición de comienzo de la cabeza de la serpiente. 
 * El símbolo 'D' representará la dirección de movimiento inicial de la serpiente y debe estar pegado al símbolo 'H'. 
 * Cualquier otro símbolo distinto de '\n' se interpretará como espacio vacío. 
 * Los símbolos se dispondrán en la forma del mapa y el conjunto debe tener forma rectangular.
 */
void snakeMap_t::loadMapScheme(string path){
	// Borramos el array actual si lo hay
	if(wallPos != NULL){
		delete [] wallPos;
		wallPos = NULL;
	}

	// Apertura del fichero
	string temp = MAP_PATH;
	temp += path;
	std::ifstream input(temp.c_str());
	if(!input.is_open()){
		fprintf(stderr, "snakeMap_t::loadMapScheme: No se ha podido abrir el archivo.\n");
		return;
	}

	string buffer;
	bool headFound = false;
	int lineCharCount = -1, wallCount = 0, dirCount = 0;
	int x, y = 0;

	// Lectura del fichero
	while(!input.eof()){
		getline(input, buffer);
		if(lineCharCount == -1)
			lineCharCount = buffer.length();
		else if(lineCharCount != (int)buffer.length()){
			fprintf(stderr, "snakeMap_t::loadMapScheme: El archivo tiene líneas de distinto tamaño (%d != %d).\n", lineCharCount, buffer.length());
			input.close();
			return;
		}
		for(x = 0; x < lineCharCount; x++){
			// Las 'X' representan muros
			if(buffer[x] == 'X') wallCount++;

			// La 'H' representa la cabeza de la serpiente
			else if(buffer[x] == 'H'){
				if(headFound){
					fprintf(stderr, "snakeMap_t::loadMapScheme: El archivo contiene más de una cabeza.\n");
					input.close();
					return;
				}
				headFound = true;

				// La 'D' representa la dirección de la serpiente y debe estar pegada a la 'H', pero no diagonalmente
				// Comprobamos si la 'D' está en la misma línea
				if(dirCount == 1 && x > 0 && buffer[x-1] == 'D')
					snake->setPos(x, y, MOVE_LEFT);
				else if(dirCount == 0 && x < lineCharCount-1 && buffer[x+1] == 'D')
					snake->setPos(x, y, MOVE_RIGHT);

				// Comprobamos si la 'D' está arriba o abajo
				else {
					bool dirFound = false;
					std::streamoff readPos = input.tellg();

					// Si acabamos de leer al menos la segunda línea, volvemos a leer la línea anterior y buscamos la 'D'
					if(dirCount == 1 && readPos > std::ios::beg + 2*(lineCharCount + 2)){
						input.seekg(readPos - 2*(lineCharCount + 2));
						getline(input, temp);
						if(temp[x] == 'D'){
							dirFound = true;
							snake->setPos(x, y, MOVE_UP);
						}
					}

					// Leemos la línea siguiente para ver si la 'D' está debajo. Si no está, la 'D' no se ha encontrado y el mapa está mal diseñado
					if(!dirFound){
						input.seekg(readPos);
						getline(input, temp);
						if((int)temp.length() == lineCharCount && temp[x] == 'D')
							snake->setPos(x, y, MOVE_DOWN);
						else {
							fprintf(stderr, "snakeMap_t::loadMapScheme: El archivo no especifica correctamente la dirección de la serpiente (Utilizar 'D').\n");
							input.close();
							return;
						}
					}
					input.seekg(readPos);
				}
			}

			// Contamos el número de direcciones que hay para no permitir que haya más de una y para evitar buscar hacia atrás si sabemos que no hay nada
			else if(buffer[x] == 'D' && ++dirCount > 1){
				fprintf(stderr, "snakeMap_t::loadMapScheme: El archivo contiene más de un indicador de dirección.\n");
				snake->setPos(0, 0, MOVE_UP);
				input.close();
				return;
			}
		}
		y++;
	}

	if(!headFound){
		fprintf(stderr, "snakeMap_t::loadMapScheme: El archivo no especificaba la posición inicial de la serpiente (Utilizar 'H').\n");
		snake->setPos(0, 0, MOVE_UP);
		input.close();
		return;
	}

	if(tileSize > 0 && background != NULL && (((y+1)*tileSize != background->height()) || (lineCharCount*tileSize != background->width())))
		fprintf(stderr, "snakeMap_t::loadMapScheme: [WARNING] Las dimensiones del mapa cargado no coinciden con las dimensiones del fondo.\n");

	// Creamos el nuevo array de posiciones de los muros
	nWalls = wallCount;
	wallPos = new coord[nWalls];

	// Damos las posiciones a los muros
	if(wallPos != NULL){
		int i;
		input.seekg(std::ios::beg);
		for(i = 0, wallCount = 0, y = 0; wallCount < nWalls; y++){
			getline(input, buffer);
			for(x = 0; x < lineCharCount; x++){
				if(buffer[x] == 'X'){
					wallPos[i].x = x;
					wallPos[i].y = y;
					wallCount++; i++;
				}
			}
		}
	}
	else
		fprintf(stderr, "snakeMap_t::loadMapScheme: No se ha podido reservar memoria para el array de muros.\n");

	input.close();
}

/**
 * @brief Le asigna una imagen (tileset) a la serpiente.
 * @param path Nombre de la imagen.
 * @param size Tamaño de los tiles.
 * @note No se puede asignar un tamaño de tiles diferente a la serpiente y las comidas.
 * @see snakeMap_t::setFoodImg
 *
 * Hay que asignar el tamaño de los tiles al menos en una de las dos funciones.
 */
void snakeMap_t::setSnakeImg(string path, int size){
	if(snakeTiles != NULL){
		delete snakeTiles;
		snakeTiles = NULL;
	}

	snakeTiles = new image_t(path);
	if(snakeTiles == NULL)
		fprintf(stderr, "snakeMap_t::setSnakeImg: No se ha podido cargar la imagen.\n");
	else {
		if(tileSize == -1)
			tileSize = size;
		else if(size != -1 && tileSize != size)
			fprintf(stderr, "snakeMap_t::setSnakeImg: Se ha intentado asignar dos tamaños de tiles diferentes.\n");
	}
}

/**
 * @brief Le asigna una imagen (tileset) a las comidas.
 * @param path Nombre de la imagen.
 * @param size Tamaño de los tiles.
 * @note No se puede asignar un tamaño de tiles diferente a la serpiente y las comidas.
 * @see snakeMap_t::setSnakeImg
 *
 * Hay que asignar el tamaño de los tiles al menos en una de las dos funciones.
 */
void snakeMap_t::setFoodImg(string path, int size){
	if(special != NULL){
		delete special;
		special = NULL;
	}

	special = new image_t(path);
	if(special == NULL)
		fprintf(stderr, "snakeMap_t::setFoodImg: No se ha podido cargar la imagen.\n");
	else {
		if(tileSize == -1)
			tileSize = size;
		else if(size != -1 && tileSize != size)
			fprintf(stderr, "snakeMap_t::setFoodImg: Se ha intentado asignar dos tamaños de tiles diferentes.\n");
	}
}

/**
 * @brief Devuelve la anchura del mapa en la pantalla.
 * @return Anchura del mapa ó 0 si no se ha cargado un fondo.
 */
int snakeMap_t::width(void) const {
	return (background != NULL)? background->width() : 0;
}

/**
 * @brief Devuelve la altura del mapa en la pantalla.
 * @return Altura del mapa ó 0 si no se ha cargado un fondo.
 */
int snakeMap_t::height(void) const {
	return (background != NULL)? background->height() : 0;
}

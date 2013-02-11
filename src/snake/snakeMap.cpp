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
snakeMap_t::snakeMap_t(): wallPos(NULL), nWalls(0), background(NULL), special(NULL), tileSize(-1), moveFreq(1), foodLimit(-1), timeLimit(-1), snake(NULL) {
	snake = new snake_t;
	setPos(0, 0);
}

/**
 * @brief Contructor. Inicializa la clase y coloca el mapa en la pantalla.
 * @param posX Posición en el eje X en la que se colocará el comienzo del mapa en la pantalla.
 * @param posY Posición en el eje Y en la que se colocará el comienzo del mapa en la pantalla.
 */
snakeMap_t::snakeMap_t(int posX, int posY): wallPos(NULL), nWalls(0), background(NULL), special(NULL), tileSize(-1), moveFreq(1), foodLimit(-1), timeLimit(-1), snake(NULL) {
	snake = new snake_t;
	setPos(posX, posY);
}

/**
 * @brief Constructor. Inicializa la clase, coloca el mapa en la pantalla y le asigna una imagen de fondo.
 * @param posX Posición en el eje X en la que se colocará el comienzo del mapa en la pantalla.
 * @param posY Posición en el eje Y en la que se colocará el comienzo del mapa en la pantalla.
 * @param path Nombre de la imagen de fondo del mapa.
 */
snakeMap_t::snakeMap_t(int posX, int posY, string path): wallPos(NULL), nWalls(0), background(NULL), special(NULL), tileSize(-1), moveFreq(1), foodLimit(-1), timeLimit(-1), snake(NULL) {
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
 * Los símbolos se dispondrán en la forma del mapa y debe tener forma rectangular el conjunto.
 */
void snakeMap_t::loadMapScheme(string path){
	string temp = MAP_PATH;
	temp += path;
	std::ifstream input(temp.c_str());
	if(!input.is_open()){
		fprintf(stderr, "snakeMap_t::loadMapScheme: No se ha podido abrir el archivo.\n");
		return;
	}

	string buffer;
	bool headFound = false;
	int lineCharCount = -1, wallCount = 0;
	int x, y = 0;
	std::streamoff readPos;
	while(!input.eof()){
		getline(input, buffer);
		if(lineCharCount == -1)
			lineCharCount = buffer.length();
		else if(lineCharCount != buffer.length()){
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
				if(x > 0 && buffer[x-1] == 'D')
					snake->setPos(x, y, MOVE_LEFT);
				else if(x < lineCharCount-1 && buffer[x+1] == 'D')
					snake->setPos(x, y, MOVE_RIGHT);

				// Comprobamos si la 'D' está arriba o abajo
				else {
					bool dirFound = false;
					readPos = input.tellg();

					// Si acabamos de leer al menos la segunda línea, volvemos a leer la línea anterior y buscamos la 'D'
					if(readPos > std::ios::beg + 2*(lineCharCount + 2)){
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
						if(temp.length() == lineCharCount && temp[x] == 'D')
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
		}
		y++;
	}
	input.close();

	if(!headFound){
		fprintf(stderr, "snakeMap_t::loadMapScheme: El archivo no especificaba la posición inicial de la serpiente (Utilizar 'H').\n");
		snake->setPos(0, 0, MOVE_UP);
	}

	printf("Dimensiones del mapa: %d x %d\n", lineCharCount, y);
	printf("Número de paredes: %d\n", wallCount);
}

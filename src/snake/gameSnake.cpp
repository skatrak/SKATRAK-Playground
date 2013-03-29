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
// SDL
#include "SDL/SDL.h"
// Propias
#include "SKATRAK_PLAYGROUND.hpp"
#include "shared_attributes.hpp"
#include "system.hpp"
#include "image.hpp"
#include "font.hpp"
#include "inifile.hpp"
#include "timekeeper.hpp"
#include "snake/snakePiece.hpp"
#include "snake/snakeMap.hpp"

int loadMaplist(string fileName, string*& schemeNameList, int& nMaps);

returnVal gameSnake(void*){
	// Música del juego
	loadTracklist("snake_setlist.ini");

	// Fondo de la pantalla
	SDL_Surface* screen = sistema->scr();
	image_t background("snake/fondo_prueba.png");

	// La serpiente
	snakeMap_t snakemap;
	snakemap.setBackground("snake/mapa_fondo_prueba.png");
	snakemap.setPos((sistema->width() - snakemap.width()) / 2, 32);
	snakemap.setSnakeImg("snake/serpiente_prueba.png", 16);
	snakemap.setFoodImg("snake/comida_prueba.png");

	// Cargamos del archivo de configuración la lista de mapas
	string* lista = NULL;
	int nMaps = 0, indiceMapa = 0;
	if(loadMaplist("snake_maplist.ini", lista, nMaps) < 0){
		fprintf(stderr, "gameSnake: No se ha podido cargar la lista de mapas.\n");
		return ACTUAL_MENU;
	}
	snakemap.loadMapScheme(lista[indiceMapa]);

	// Números pequeños para probar su correcto funcionamiento
	snakemap.setFoodLimit(22);
	snakemap.setTimeLimit(5400);	// 3 minutos a 30 fps

	// Información de la partida en la pantalla
	char texto[17];
	font_t puntText("AlteHaasGroteskRegular.ttf");
	puntText.setColor(0, 0, 255);
	puntText.setSize(48);
	puntText.setText("Puntuación: 0");

	// Game loop
	int puntuacion = 0;
	SDL_Event event;
	timekeeper_t timer;
	while(true){
		timer.refresh();
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_UP:
					snakemap.turnSnake(MOVE_UP);
					break;
				case SDLK_DOWN:
					snakemap.turnSnake(MOVE_DOWN);
					break;
				case SDLK_LEFT:
					snakemap.turnSnake(MOVE_LEFT);
					break;
				case SDLK_RIGHT:
					snakemap.turnSnake(MOVE_RIGHT);
					break;
				case SDLK_ESCAPE:
					loadTracklist("menu_setlist.ini");
					delete [] lista;
					return ACTUAL_MENU;
				default: break;
				}
				break;
			case SDL_QUIT:
				delete [] lista;
				return EXIT;
			default: break;
			}
		}
		// Lógica del juego
		if(timer.renderedFrames() == 5){
			timer.resetFrames();
			switch(snakemap.update()){
			case HIT_NONE:
				break;
			case HIT_BONUS:
				puntuacion += 5;	// Deliberadamente sin 'break' para que se sume más a la puntuación
			case HIT_NORMAL:
				puntuacion += 5;
				break;
			case HIT_DEATH:
				loadTracklist("menu_setlist.ini");
				delete [] lista;
				return ACTUAL_MENU;
			case HIT_WARP:	// Cargamos el mapa siguiente
				if(indiceMapa < nMaps)
					snakemap.loadMapScheme(lista[++indiceMapa]);
				else {
					delete [] lista;
					return MAIN;
				}
				break;
			}
		}

		// Imprimir por pantalla
		sprintf(texto, "Puntuación: %d", puntuacion);
		puntText.setText(texto);
		background.blit(0, 0, screen);
		puntText.blit(snakemap.posX(), snakemap.posY() + snakemap.height() + 16, screen);
		snakemap.blit(screen);
		sistema->update();
		timer.waitFramerate(30);
	}
}

int loadMaplist(string fileName, string*& schemeNameList, int& nMaps){
	inifile_t config(fileName);
	if(config.errorStatus()){
		fprintf(stderr, "loadMapList: %s\n", config.errorString().c_str());
		return -1;
	}

	nMaps = config.readInt("Map", "Cantidad");
	if(config.errorStatus()){
		fprintf(stderr, "loadMapList: %s\n", config.errorString().c_str());
		return -1;
	}

	schemeNameList = new string[nMaps];

	char nombre[7];
	for(int i = 0; i < nMaps; ++i){
		sprintf(nombre, "Mapa%d", i+1);
		schemeNameList[i] = config.readString("Map", nombre);
		if(config.errorStatus()){
			fprintf(stderr, "loadMapList: %s\n", config.errorString().c_str());
			delete [] schemeNameList;
			schemeNameList = NULL;
			return -1;
		}
	}
	return 0;
}

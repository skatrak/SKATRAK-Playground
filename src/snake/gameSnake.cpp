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
#include "timekeeper.hpp"
#include "snake/snakePiece.hpp"
#include "snake/snakeMap.hpp"

returnVal gameSnake(void*){
	// Fondo de la pantalla
	SDL_Surface* screen = sistema->scr();
	image_t background("fondo_inicio_prueba.png");

	// La serpiente
	snakeMap_t snakemap(10, 10, "snake/serpiente_mapa_fondo_prueba.png");
	snakemap.loadMapScheme("mapasnake_prueba.txt");
	snakemap.setSnakeImg("snake/serpiente_pruebav2.png", 32);
	snakemap.setFoodImg("snake/serpiente_comida_prueba.png");
	// Números pequeños para probar su correcto funcionamiento
	snakemap.setFoodLimit(25);
	snakemap.setTimeLimit(150);

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
					return ACTUAL_MENU;
				default: break;
				}
				break;
			case SDL_QUIT:
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
				printf("Has muerto. Puntuación: %d\n", puntuacion);
				return ACTUAL_MENU;
			case HIT_WARP:	// Aquí se podría cargar otro mapa, etc...
				printf("Has ganado. Puntuación: %d\n", puntuacion);
				return MAIN;
			}
		}

		// Imprimir por pantalla
		background.blit(0, 0, screen);
		snakemap.blit(screen);
		sistema->update();
		timer.waitFramerate(30);
	}
}

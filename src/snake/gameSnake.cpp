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
#include <shared_attributes.hpp>
#include <snake/snakePiece.hpp>
#include <snake/snake.hpp>

returnVal gameSnake(void*){
	// Inicialización de la semilla
	srand(SDL_GetTicks());

	// Fondo de la pantalla
	SDL_Surface* screen = sistema->scr();
	image_t background("fondo_inicio_prueba.png");
	image_t foodImg("snake/serpiente_comida_prueba.png");

	// La serpiente
	snake_t snake;
	snake.setPos(10, 10, MOVE_RIGHT);
	snake.setImg("snake/serpiente_pruebav2.png", 32);
	int headX, headY, foodX = -1, foodY = -1;

	// Colocamos la primera comida
	foodX = rand() % (int)(sistema->width()/32);
	foodY = rand() % (int)(sistema->height()/32);

	// Game loop
	SDL_Event event;
	timekeeper_t timer;
	while(true){
		timer.refresh();
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_UP:
					snake.turn(MOVE_UP);
					break;
				case SDLK_DOWN:
					snake.turn(MOVE_DOWN);
					break;
				case SDLK_LEFT:
					snake.turn(MOVE_LEFT);
					break;
				case SDLK_RIGHT:
					snake.turn(MOVE_RIGHT);
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
		if(timer.renderedFrames() == 2){
			timer.resetFrames();
			snake.step();
			if(snake.headPos(&headX, &headY) >= 0){
				if(headX >= (sistema->width()/32))
					snake.setHeadPos(0, headY);
				else if(headX < 0)
					snake.setHeadPos((sistema->width()/32)-1, headY);
				if(headY >= (sistema->height()/32))
					snake.setHeadPos(headX, 0);
				else if(headY < 0)
					snake.setHeadPos(headX, (sistema->height()/32)-1);
			}
			if(headX == foodX && headY == foodY){
				snake.addPiece(3);
				do {
					foodX = rand() % (int)(sistema->width()/32);
					foodY = rand() % (int)(sistema->height()/32);
				} while(foodX == headX && foodY == headY);
			}
			if(snake.checkCollision()){
				printf("Te mordiste la cola.\n");
				return ACTUAL_MENU;
			}
		}

		// Imprimir por pantalla
		background.blit(0, 0, screen);
		foodImg.blit(foodX*32, foodY*32, screen);
		snake.blit(screen, 0, 0);
		sistema->update();
		timer.waitFramerate(30);
	}
}

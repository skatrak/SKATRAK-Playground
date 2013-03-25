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
#include "timekeeper.hpp"
#include "menu.hpp"

/* Definición de las funciones de callback comunes */
returnVal defaultCallback(void* data){ return ACTUAL_MENU; }
returnVal backCallback(void* data){ return PREV_MENU; }
returnVal exitCallback(void* data){ return EXIT; }

/* Declaraciones de los submenús del menú principal */
returnVal mainConecta4(void* data);
returnVal mainSnake(void* data);

returnVal mainMenu(){
	menu_t menu(5);

	menu.setTexts("BOOTERFF.ttf", 48);

	menu.setText(0, "Conecta 4");
	menu.setOpt(0, &mainConecta4);
	menu.setText(1, "Snake");
	menu.setOpt(1, &mainSnake);
	menu.setText(2, "Opciones");
	menu.setOpt(2, &defaultCallback);
	menu.setText(3, "Salir");
	menu.setOpt(3, &exitCallback);
	menu.setText(4, "Acerca de...");
	menu.setOpt(4, &defaultCallback);

	menu.setBackground("menu_prueba.png");
	menu.setImage("marcador_prueba.png");
	menu.align(0);

	SDL_Event event;
	SDL_Surface* screen = sistema->scr();
	timekeeper_t timer;

	while(true){
		timer.refresh();
		while(SDL_PollEvent(&event)){
			switch(menu.update(&event)){
			case ERROR:
				fprintf(stderr, "Saliendo del menú principal con un error.\n");
				return ERROR;
			case EXIT:
			case PREV_MENU:
				return EXIT;
			case ACTUAL_MENU:
			case MAIN:
			default: break;
			}
		}
		menu.blit(screen);
		sistema->update();

		timer.waitFramerate(30);
	}
	return ERROR;
}

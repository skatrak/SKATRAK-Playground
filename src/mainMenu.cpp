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

#include "../include/SKATRAK_PLAYGROUND.hpp"
#include "../include/shared_attributes.hpp"
#include "../include/menu.hpp"

returnVal defaultCallback(void* data){
	printf("Entraste a algún juego.\n");
	return EXIT;
}

returnVal optionsCallback(void* data){
//	return optionsMenu();
	printf("Entraste al menú de opciones.\n");
	return ACTUAL_MENU;
}

returnVal aboutCallback(void* data){
//	return aboutMenu();
	printf("Entraste al menú 'Acerca de...'.\n");
	return ACTUAL_MENU;
}

returnVal exitCallback(void* data){
	printf("Salir.\n");
	return EXIT;
}

returnVal mainMenu(){
	menu_t menu(5);

	menu.setTexts("font01.ttf", 48);

	menu.setText(0, "Juego 1");
	menu.setOpt(0, &defaultCallback);

	menu.setText(1, "Juego 2");
	menu.setOpt(1, &defaultCallback);

	menu.setText(2, "Opciones");
	menu.setOpt(2, &optionsCallback);

	menu.setText(3, "Salir");
	menu.setOpt(3, &exitCallback);

	menu.setText(4, "Acerca de...");
	menu.setOpt(4, &aboutCallback);

	menu.setBackground("Fondo_inicio_prueba.png");
	menu.setImage("marcador_prueba.png");
	menu.align(0);

	SDL_Event event;
	SDL_Surface* screen = sistema->scr();
	timekeeper_t timer;
	bool salir = false;
	while(!salir){
		timer.refresh();
		while(SDL_PollEvent(&event)){
			switch(menu.update(&event)){
				case EXIT:
				case PREV_MENU:
					salir = true;
					break;
				case ACTUAL_MENU:
				case MAIN:
				default: break;
			}
		}
		menu.blit(screen);
		sistema->update();
		timer.waitFramerate(30);
	}
	printf("Has estado %d segundos en el menú principal.\n", (int)(timer.elapsed()/1000));
	return EXIT;
}

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
	return EXIT;
}

returnVal mainMenu(){
	menu_t menu(4);
	for(int i = 0; i < 4; i++)
		menu.setOpt(i, &defaultCallback);
	menu.setTexts("font01.ttf", 48);
	menu.setText(0, "op1");
	menu.setText(1, "op2");
	menu.setText(2, "op3");
	menu.setText(3, "op4");
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
					salir = true;
					break;
				case ACTUAL_MENU:
				default:
					break;
			}
		}
		menu.blit(screen);
		sistema->update();
		timer.waitFramerate(30);
	}
	printf("Has estado %d segundos en el menú principal.\n", (int)(timer.elapsed()/1000));
	return EXIT;
}

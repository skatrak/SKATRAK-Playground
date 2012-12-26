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
#include <conecta4/tablero.hpp>

// TODO: Arreglar lo de que la bola se repite por la pantalla
returnVal Game_Conecta4(void* data){
	SDL_Surface* screen = sistema->scr();
	SDL_Event event;

	image_t fondo("Fondo_Conecta4_prueba.png");

	tablero_t tablero(0, 48);
	tablero.setTab("Tab_Conecta4.png");
	tablero.setMark(0, "Mark_Conecta4_P1.png");
	tablero.setMark(1, "Mark_Conecta4_P2.png");
	tablero.setFich(0, "Ficha_Conecta4_P1.png");
	tablero.setFich(1, "Ficha_Conecta4_P2.png");
	tablero.setSFX("Pin Drop.wav");

	timekeeper_t timer;
	while(true){
		timer.refresh();
		while(SDL_PollEvent(&event)){
			tablero.update(&event);
			switch(event.type){
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE) return ACTUAL_MENU;
				break;
			case SDL_QUIT:
				return EXIT;
			}
			switch(tablero.checkWin()){
			case NOT_FINISHED:
				break;
			case P1_WINS:
				printf("Ha ganado el jugador 1.\n");
				tablero.reset();
				break;
			case P2_WINS:
				printf("Ha ganado el jugador 2.\n");
				tablero.reset();
				break;
			case NOBODY_WINS:
				printf("Empate.\n");
				tablero.reset();
				break;
			}
		}
		fondo.blit(0, 0, screen);
		tablero.blit(screen);
		sistema->update();
		timer.waitFramerate(30);
	}
	return ERROR;
}

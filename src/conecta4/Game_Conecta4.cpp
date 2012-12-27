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

#ifdef _MSC_VER
#define sprintf sprintf_s
#endif

returnVal Game_Conecta4(void* data){
	SDL_Surface* screen = sistema->scr();
	SDL_Event event;
	static int victorias[2] = {0, 0}; // Lo hacemos estático para que las puntuaciones se guarden mientras no se cierre el juego
	char letreroJugador[32];

	// Imagen de fondo del juego y marcador
	image_t fondo("Fondo_Conecta4_prueba.png");
	image_t mark("marcador_prueba.png");

	// Creamos las fuentes que va a utilizar el juego
	font_t j1("font01.ttf");
	j1.setColor(255, 255, 255);
	j1.setSize(32);
	font_t j2(j1);
	font_t reset(j1);
	font_t atras(j1);
	font_t tiempo(j1);
	reset.setText("Reiniciar");
	atras.setText("Atras");

	// Creamos el tablero
	tablero_t tablero;
	tablero.setTab("Tab_Conecta4.png");
	tablero.setPos((int)(screen->w / 2 - tablero.width() / 2), (int)(screen->h - tablero.height() - tablero.height() / 6));
	tablero.setMark(0, "Mark_Conecta4_P1.png");
	tablero.setMark(1, "Mark_Conecta4_P2.png");
	tablero.setFich(0, "Ficha_Conecta4_P1.png");
	tablero.setFich(1, "Ficha_Conecta4_P2.png");
	tablero.setSFX("Pin Drop.wav");

	// Posiciones del mensaje de Atrás y de Reiniciar
	struct msgCoord {
		int x;
		int y;
	};
	msgCoord resC = {tablero.posX(), j1.height()};
	msgCoord atrC = {tablero.posX() + tablero.width() - atras.width(), j2.height()};

	// Para saber si hay algún botón seleccionado
	enum optSelected { NONE, RESET, BACK };
	optSelected selected = NONE;

	// Game loop
	timekeeper_t timer;
	while(true){
		timer.refresh();
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_MOUSEMOTION:
				if(event.motion.x >= resC.x && event.motion.x <= resC.x + reset.width() && event.motion.y >= resC.y && event.motion.y <= resC.y + reset.height())
					selected = RESET;
				else if(event.motion.x >= atrC.x && event.motion.x <= atrC.x + atras.width() && event.motion.y >= atrC.y && event.motion.y <= atrC.y + atras.height())
					selected = BACK;
				else
					selected = NONE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT && selected != NONE){
					if(selected == RESET){
						tablero.reset();
						continue;
					}
					else /* if(salir()) */
						return ACTUAL_MENU;
				}
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE /* && salir() */) return ACTUAL_MENU;
				break;
			case SDL_QUIT:
				return EXIT;
			}
			tablero.update(&event);
			switch(tablero.checkWin()){
			case NOT_FINISHED:
				break;
			case P1_WINS:
				/* msgVictoria(P1_WINS) */
				printf("Ha ganado el jugador 1.\n");
				victorias[0]++;
				tablero.reset();
				break;
			case P2_WINS:
				/* msgVictoria(P2_WINS) */
				printf("Ha ganado el jugador 2.\n");
				victorias[1]++;
				tablero.reset();
				break;
			case NOBODY_WINS:
				/* msgVictoria(NOBODY_WINS) */
				printf("Empate.\n");
				tablero.reset();
				break;
			}
		}
		// Textos de las puntuaciones y tiempo transcurrido
		sprintf(letreroJugador, "Jugador 1: %d victorias", victorias[0]);
		j1.setText(letreroJugador);
		sprintf(letreroJugador, "Jugador 2: %d victorias", victorias[1]);
		j2.setText(letreroJugador);
		sprintf(letreroJugador, "%.2d:%.2d", (int)(timer.elapsed() / 60000), (int)(timer.elapsed() / 1000) % 60);
		tiempo.setText(letreroJugador);
		// Mostramos todo por pantalla
		fondo.blit(0, 0, screen);
		tablero.blit(screen);
		if(selected == RESET)
			mark.blit(resC.x, resC.y + (reset.height() - mark.height()), screen);
		else if(selected == BACK)
			mark.blit(atrC.x, atrC.y + (atras.height() - mark.height()), screen);
		j1.blit(tablero.posX(), 0, screen);
		j2.blit(tablero.posX() + tablero.width() - j2.width(), 0, screen);
		reset.blit(resC.x, resC.y, screen);
		atras.blit(atrC.x, atrC.y, screen);
		tiempo.blit((int)((sistema->width() / 2) - (tiempo.width() / 2)), tablero.posY() + tablero.height() + 5, screen);
		// Intercambiamos los buffers de vídeo y fijamos los FPS
		sistema->update();
		timer.waitFramerate(30);
	}
	return ERROR;
}

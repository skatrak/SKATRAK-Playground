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

bool msgSalir(bool tablero_vacio);
bool msgReset(bool tablero_vacio);
void msgVictoria(ResultConecta4 ganador);

returnVal gameConecta4(void* data){
	SDL_Surface* screen = sistema->scr();
	SDL_Event event;
	static int victorias[2] = {0, 0}; // Lo hacemos estático para que las puntuaciones se guarden mientras no se cierre el juego
	char letreroJugador[32];
	const int GAME_FONT_OFFSET = 15;

	// Imagen de fondo del juego y marcador
	image_t fondo("conecta4/fondo_prueba.png");
	image_t mark("marcador_prueba.png");

	// Creamos las fuentes que va a utilizar el juego
	font_t j1("AlteHaasGroteskRegular.ttf");
	j1.setColor(255, 255, 255);
	j1.setSize(32);
	font_t j2(j1);
	font_t reset(j1);
	font_t atras(j1);
	font_t tiempo(j1);
	reset.setText("Reiniciar");
	atras.setText("Atrás");

	// Creamos el tablero
	tablero_t tablero;
	tablero.setTab("conecta4/tab.png");
	tablero.setPos((int)(screen->w / 2 - tablero.width() / 2), (int)(screen->h - tablero.height() - tablero.height() / 6));
	tablero.setMark(0, "conecta4/mark_P1.png");
	tablero.setMark(1, "conecta4/mark_P2.png");
	tablero.setFich(0, "conecta4/ficha_P1.png");
	tablero.setFich(1, "conecta4/ficha_P2.png");
	tablero.setSFX("Pin Drop.wav");

	// Posiciones del mensaje de Atrás y de Reiniciar
	struct msgCoord {
		int x;
		int y;
	};
	msgCoord resC = {tablero.posX(), j1.height() + 2*GAME_FONT_OFFSET};
	msgCoord atrC = {tablero.posX() + tablero.width() - atras.width(), j2.height() + 2*GAME_FONT_OFFSET};

	// Para saber si hay algún botón seleccionado
	enum optSelected { NONE, RESET, BACK };
	optSelected selected = NONE;

	// Jugador que empezó la partida actual (Para el reset)
	int startPlayer = 0;
	// Estado de la partida tras la última comprobación
	ResultConecta4 estado = NOT_FINISHED;

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
						if(msgReset(tablero.isEmpty())){
							tablero.reset();
							tablero.setPlayer(startPlayer);
						}
						continue;
					}
					else if(msgSalir(tablero.isEmpty()))
						return ACTUAL_MENU;
					event.type = SDL_KEYUP; // Cambiamos el tipo de evento para que no caiga una ficha en el tablero por haber pulsado reset o atrás
				}
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE && msgSalir(tablero.isEmpty()))
					return ACTUAL_MENU;
				break;
			case SDL_QUIT:
				return EXIT;
			}
			// Dejamos esto aquí porque no puede cambiar el estado del juego cuando no hay eventos, así evitamos comprobaciones innecesarias
			tablero.update(&event);
			estado = tablero.checkWin();
			if(estado != NOT_FINISHED){
				if(estado == P1_WINS)
					victorias[0]++;
				else if(estado == P2_WINS)
					victorias[1]++;
				msgVictoria(estado);
				tablero.reset();
				startPlayer = tablero.actualPlayer();
			}
		}
		// Textos de las puntuaciones y tiempo transcurrido
		sprintf(letreroJugador, "Jugador 1: %d victorias", victorias[0]);
		j1.setText(letreroJugador);
		sprintf(letreroJugador, "Jugador 2: %d victorias", victorias[1]);
		j2.setText(letreroJugador);
		sprintf(letreroJugador, "%.2d:%.2d:%.2d", (int)(timer.elapsed() / 3600000), (int)(timer.elapsed() / 60000) % 60, (int)(timer.elapsed() / 1000) % 60);
		tiempo.setText(letreroJugador);
		// Mostramos todo por pantalla
		fondo.blit(0, 0, screen);
		tablero.blit(screen);
		if(selected == RESET)
			mark.blit(resC.x, resC.y + (int)((reset.height() - mark.height()) / 2), screen);
		else if(selected == BACK)
			mark.blit(atrC.x, atrC.y + (int)((atras.height() - mark.height()) / 2), screen);
		j1.blit(tablero.posX(), GAME_FONT_OFFSET, screen);
		j2.blit(tablero.posX() + tablero.width() - j2.width(), GAME_FONT_OFFSET, screen);
		reset.blit(resC.x, resC.y, screen);
		atras.blit(atrC.x, atrC.y, screen);
		tiempo.blit((int)((sistema->width() / 2) - (tiempo.width() / 2)), tablero.posY() + tablero.height() + (int)(((sistema->height() - (tablero.posY() + tablero.height())) / 2) - tiempo.height() / 2), screen);
		// Intercambiamos los buffers de vídeo y fijamos los FPS
		sistema->update();
		timer.waitFramerate(30);
	}
	return ERROR;
}

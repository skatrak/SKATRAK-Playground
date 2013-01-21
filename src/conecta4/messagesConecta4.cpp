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

bool salir(bool tablero_vacio){
	if(tablero_vacio) return true;

	SDL_Surface* screen = sistema->scr();
	// Creamos las fuentes del mensaje
	font_t msg("font01.ttf");
	msg.setColor(255, 255, 255);
	msg.setSize(32);
	font_t si(msg);
	font_t no(msg);
	// Escribimos los mensajes en las fuentes
	msg.setText("Deseas abandonar la partida?");
	si.setText("SI");
	no.setText("NO");
	// Cargamos las imágenes sobre las que poner el mensaje
	image_t fondoMsg("ventana_prueba.png");
	SDL_Rect mark;

	bool selected = 1; // 1 = BOTÓN SI, 0 = BOTÓN NO

	struct msgPos {
		int x;
		int y;
	};
	msgPos fondoPos = {(int)((sistema->width() - fondoMsg.width()) / 2), (int)((sistema->height() - fondoMsg.height()) / 2)};
	msgPos siPos = {fondoPos.x + (int)((fondoMsg.width() / 4) - (si.width() / 2)), fondoPos.y + (int)((3 * fondoMsg.height() / 4) - (si.height() / 2))};
	msgPos noPos = {fondoPos.x + (int)((3 * fondoMsg.width() / 4) - (no.width() / 2)), fondoPos.y + (int)((3 * fondoMsg.height() / 4) - (no.height() / 2))};

	SDL_Event event;
	SDL_Surface* background = SDL_ConvertSurface(screen, screen->format, screen->flags);
	timekeeper_t timer;
	while(true){
		timer.refresh();
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEMOTION:
					if(!selected && event.motion.x >= siPos.x && event.motion.x <= siPos.x + si.width() && event.motion.y >= siPos.y && event.motion.y <= siPos.y + si.height())
						selected = 1;
					else if(selected && event.motion.x >= noPos.x && event.motion.x <= noPos.x + no.width() && event.motion.y >= noPos.y && event.motion.y <= noPos.y + no.height())
						selected = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT){
						if(selected && event.button.x >= siPos.x && event.button.x <= siPos.x + si.width() && event.button.y >= siPos.y && event.button.y <= siPos.y + si.height())
							return true;
						if(!selected && event.button.x >= noPos.x && event.button.x <= noPos.x + no.width() && event.button.y >= noPos.y && event.button.y <= noPos.y + no.height())
							return false;
					}
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE)
						return false;
					if(event.key.keysym.sym == SDLK_RETURN)
						return selected; // Ventaja de haberla declarado bool
					if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
						selected = !selected;
					break;
				case SDL_QUIT:
					return true;
			}
		}
		// Imprimir todo por pantalla
		SDL_BlitSurface(background, NULL, screen, NULL);
		fondoMsg.blit(fondoPos.x, fondoPos.y, screen);
		if(selected){
			mark.x = siPos.x - 5;
			mark.y = siPos.y - 5;
			mark.w = si.width() + 10;
			mark.h = si.height() + 10;
		}
		else {
			mark.x = noPos.x - 5;
			mark.y = noPos.y - 5;
			mark.w = no.width() + 10;
			mark.h = no.height() + 10;
		}
		SDL_FillRect(screen, &mark, SDL_MapRGB(screen->format, 0, 255, 128));
		msg.blit((int)(sistema->width() - msg.width()) / 2, fondoPos.y + (int)((fondoMsg.height() / 4) - (msg.height() / 2)), screen);
		si.blit(siPos.x, siPos.y, screen);
		no.blit(noPos.x, noPos.y, screen);
		// Actualizar la pantalla y fijar FPS
		sistema->update();
		timer.waitFramerate(30);
	}
}

void msgVictoria(ResultConecta4 ganador){

}

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
#include <conecta4/tablero.hpp>
#include <shared_attributes.hpp>

/**
 * @brief Crea la matriz que contiene los valores de las fichas en el tablero.
 */
void tablero_t::creaTab(){
	if(tablero != NULL)
		destruyeTab();
	tablero = new CellState*[7];	// Creamos la matriz traspuesta (7x6) para que sea más eficiente colocar las piezas
	if(tablero == NULL)
		fprintf(stderr, "No se ha podido reservar espacio para el tablero del Conecta 4.\n");
	else {
		for(int i = 0; i < 7; i++){
			tablero[i] = NULL;
			tablero[i] = new CellState[6];
			if(tablero[i] == NULL){
				fprintf(stderr, "Error al reservar espacio para el tablero del Conecta 4.\n");
				i--;
				while(i >= 0){
					delete [] tablero[i];
					tablero[i] = NULL;
					i--;
				}
				delete [] tablero;
				tablero = NULL;
				break;
			}
		}
	}
}

/**
 * @brief Libera la memoria asignada al tablero.
 */
void tablero_t::destruyeTab(){
	if(tablero != NULL){
		for(int i = 0; i < 7; i++){
			delete [] tablero[i];
			tablero[i] = NULL;
		}
		delete [] tablero;
		tablero = NULL;
	}
	posicion.w = posicion.h = 0;
}

/**
 * @brief Hace una animación al dejar caer una ficha.
 * @note Esta función bloquea el juego y no dejará que continue hasta que termine.
 */
void tablero_t::soltarFicha(){
	int tmp = 5;
	int pos;
	while(tablero[columna][tmp] != CELL_EMPTY)
		tmp--;

	// En tmp está el índice de la primera casilla libre. Vamos a calcular su posición en la pantalla
	pos = posicion.y + (tmp+1)*(FICHA_OFFSET) + tmp*ficha[jugador]->height();
	// En pos está la posición en y en la que se debe llevar a cabo el rebote

	timekeeper_t timer;
	int posx = posicion.x + (columna+1)*(FICHA_OFFSET) + columna*ficha[jugador]->width();
	int posy = posicion.y - ficha[jugador]->height();
	double vel = 0.0; // Velocidad en px/fot
	double accel = -0.6968888889; // Gravedad en px/fot ^ 2 (64 px = 1m, 1s = 30 fot)
	double COR = 0.75; // Coeficiente de restitución

	if(ficha[jugador] != NULL){
		do {
			timer.refresh();
			vel += accel;
			posy -= (int)vel;
			if(posy <= pos){
				if(choque != NULL)
					choque->play();
				posy = pos;
				vel = -(COR * vel);
			}
			ficha[jugador]->blit(posx, posy, sistema->scr());
			blit(sistema->scr());
			timer.waitFramerate(30);
		}
		while(vel != 0 && posy != pos);
	}

	tablero[columna][tmp] = (!jugador)? CELL_P1 : CELL_P2;
}

/**
 * @brief Constructor. Inicializa las variables y crea el tablero.
 */
tablero_t::tablero_t(): jugador(0), columna(0), tablero(NULL), img_tab(NULL), choque(NULL) {
	sig[0] = sig[1] = ficha[0] = ficha[1] = NULL;
	posicion.x = posicion.y = posicion.w = posicion.h = 0;
	creaTab();
	reset();
}

/**
 * @brief Constructor. Inicializa las variables, crea el tablero y le asigna una posición.
 * @param posx Posición x del tablero.
 * @param posy Posición y del tablero.
 */
tablero_t::tablero_t(int posx, int posy): jugador(0), columna(0), tablero(NULL), img_tab(NULL), choque(NULL) {
	sig[0] = sig[1] = ficha[0] = ficha[1] = NULL;
	posicion.w = posicion.h = 0;
	creaTab();
	reset();
	setPos(posx, posy);
}

/**
 * @brief Destructor. Libera la memoria ocupada por el tablero, sus imágenes y sonidos.
 */
tablero_t::~tablero_t(){
	destruyeTab();
	if(img_tab != NULL)
		delete img_tab;
	if(choque != NULL)
		delete choque;
	for(int i = 0; i < 2; i++){
		if(sig[i] != NULL)
			delete sig[i];
		if(ficha[i] != NULL)
			delete ficha[i];
	}
}

/**
 * @brief Pone el tablero en una determinada posición.
 * @param posx Posición x del tablero.
 * @param posy Posición y del tablero.
 */
void tablero_t::setPos(int posx, int posy){
	posicion.x = posx;
	posicion.y = posy;
}

/**
 * @brief Le asigna una imagen al tablero.
 * @param path Ruta al fichero donde se encuentra la imagen del tablero.
 */
void tablero_t::setTab(string path){
	if(img_tab != NULL){
		delete img_tab;
		img_tab = NULL;
	}
	img_tab = new image_t(path);
	if(img_tab == NULL)
		fprintf(stderr, "Error al cargar la imagen del tablero del Conecta 4.\n");
	else {
		posicion.w = img_tab->width();
		posicion.h = img_tab->height();
	}
}

/**
 * @brief Asigna una imagen a un jugador para marcar su turno sobre el tablero.
 * @param player Jugador: 0 = Jugador 1; 1 = Jugador 2.
 * @param path Ruta de la imagen.
 */
void tablero_t::setMark(int player, string path){
	if(player < 0 || player >= 2){
		fprintf(stderr, "No se puede acceder al jugador %d porque no existe.\n", player+1);
		return;
	}
	if(sig[player] != NULL){
		delete sig[player];
		sig[player] = NULL;
	}
	sig[player] = new image_t(path);
	if(sig[player] == NULL)
		fprintf(stderr, "No se ha podido cargar la imagen del señalador del jugador %d.\n", player+1);
}

/**
 * @brief Asigna la imagen de las fichas de un jugador.
 * @param player Jugador: 0 = Jugador 1; 1 = Jugador 2.
 * @param path Ruta de la imagen.
 */
void tablero_t::setFich(int player, string path){
	if(player < 0 || player >= 2){
		fprintf(stderr, "No se puede acceder al jugador %d porque no existe.\n", player+1);
		return;
	}
	if(ficha[player] != NULL){
		delete ficha[player];
		ficha[player] = NULL;
	}
	ficha[player] = new image_t(path);
	if(ficha[player] == NULL)
		fprintf(stderr, "No se ha podido cargar la imagen de la ficha del jugador %d.\n", player+1);
}

/**
 * @brief Asigna un efecto de sonido al rebote de las fichas al caer.
 * @param path Ruta del archivo de sonido.
 */
void tablero_t::setSFX(string path){
	if(choque != NULL){
		delete choque;
		choque = NULL;
	}
	choque = new sfx_t(path);
	if(choque == NULL)
		fprintf(stderr, "No se ha podido cargar el efecto de sonido de la ficha del Conecta 4.\n");
}

/**
 * @brief Vacía el tablero.
 */
void tablero_t::reset(){
	if(tablero != NULL){
		for(int i = 0; i < 7; i++)
			for(int j = 0; j < 6; j++)
				tablero[i][j] = CELL_EMPTY;
	}
	else
		fprintf(stderr, "No se puede resetear el tablero porque no se ha cargado.\n");
}

/**
 * @brief Actualiza el tablero según el evento que haya generado el jugador.
 * @param event Event que se quiere analizar.
 */
void tablero_t::update(SDL_Event* event){
	if(tablero != NULL){
		switch(event->type){
		case SDL_KEYDOWN:
			switch(event->key.keysym.sym){
			case SDLK_RIGHT:
				columna = ((columna+1) % 7);
				break;
			case SDLK_LEFT:
				columna--;
				if(columna < 0) columna = 6;
				break;
			case SDLK_RETURN:
				if(tablero[columna][0] == CELL_EMPTY){
					soltarFicha();
					jugador = (jugador+1) % 2;
				}
				break;
			default: break;
			}
			break;
		case SDL_MOUSEMOTION:
// TODO: Manejar eventos de ratón
			break;
		default: break;
		}
	}
}

/**
 * @brief Muestra el tablero por pantalla.
 * @param screen Superficie sobre la que hacer el blitting.
 */
void tablero_t::blit(SDL_Surface* screen){
	if(tablero != NULL && img_tab != NULL){
		if(sig[jugador] != NULL)
			sig[jugador]->blit(posicion.x + (columna+1)*(FICHA_OFFSET) + columna*sig[jugador]->width(), posicion.y - sig[jugador]->height(), screen);
		if(ficha[0] != NULL && ficha[1] != NULL){
			for(int i = 0; i < 7; i++){
				for(int j = 5; j >= 0; j--){
					switch(tablero[i][j]){
					case CELL_P1:
						ficha[0]->blit(posicion.x + (i+1)*(FICHA_OFFSET) + i*ficha[0]->width(), posicion.y + (j+1)*(FICHA_OFFSET) + j*ficha[0]->height(), screen);
						break;
					case CELL_P2:
						ficha[1]->blit(posicion.x + (i+1)*(FICHA_OFFSET) + i*ficha[1]->width(), posicion.y + (j+1)*(FICHA_OFFSET) + j*ficha[1]->height(), screen);
						break;
					case CELL_EMPTY:
						j = -1;	// Saltamos de columna porque de aquí hacia arriba no hay nada.
						break;
					}
				}
			}
		}
		img_tab->blit(posicion.x, posicion.y, screen);
	}
	else
		fprintf(stderr, "No se puede mostrar el tablero porque no se ha cargado correctamente.\n");
}

/*
 *
 */
// TODO: Hacer la función que detecta cuando un jugador gana la partida
int tablero_t:: checkWin(){
	return -1;
}

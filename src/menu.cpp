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

#include "../include/menu.hpp"

/**
 * @brief Constructor por defecto. Inicializa los valores de la clase.
 */
menu_t::menu_t(): nOpt(0), selIndex(0), textPos(NULL), optName(NULL), selImage(NULL), backImage(NULL), clickSound(NULL), selectSound(NULL), callback(NULL)
{
}

/**
 * @brief Constructor. Inicializa todos los valores y reserva espacio para todos los botones de opciones.
 * @param optNumber Número de opciones que van a haber en el menú.
 */
menu_t::menu_t(int optNumber): nOpt(optNumber), selIndex(0), textPos(NULL), optName(NULL), selImage(NULL), backImage(NULL), clickSound(NULL), selectSound(NULL), callback(NULL) {
	setOpts(nOpt);
}

/**
 * @brief Destructor. Libera la memoria ocupada por el menú.
 */
menu_t::~menu_t(){

}

/**
 * @brief Establece el número de opciones que hay en el menú.
 * @param optNumber Nuevo número de opciones del menú.
 * @note Si llamas esta función se van a liberar todos los callbacks y los textos.
 */
void menu_t::setOpts(int optNumber){
	// Eliminamos todo lo que dependa del número de opciones
	if(textPos != NULL){
		delete [] textPos;
		textPos = NULL;
	}
	if(optName != NULL){
		delete [] optName;
		menuName = NULL;
	}
	if(callback != NULL){
		delete [] callback;
		callback = NULL;
	}

	nOpt = 0; // Acabamos de borrar todas las opciones
	selIndex = 0;

	if(optNumber > 0){
		textPos = new SDL_Rect[optNumber];
		if(textPos == NULL){
			fprintf(stderr, "No se ha podido reservar memoria para las posiciones de los textos del menú.\n");
			return;
		}
		optName = new font_t[optNumber];
		if(optName == NULL){
			fprintf(stderr, "No se ha podido reservar memoria para las fuentes de los textos de opciones del menú.\n");
			delete [] textPos;
			textPos = NULL;
			return;
		}
		callback = new MenuCallbackFunc[optNumber];
		if(callback == NULL){
			fprintf(stderr, "No se ha podido reservar memoria para las funciones de callback del menú.\n");
			delete [] textPos;
			delete [] optName;
			textPos = NULL;
			optName = NULL;
			return;
		}
		nOpt = optNumber;	// Todo se ha cargado correctamente, así que actualizamos el número de opciones que tenemos
	}
	else {
		fprintf(stderr, "No se ha especificado un número válido de opciones al menú.\n");
	}
}

/**
 * @brief
 */
void menu_t::setOpt(int optIndex, MenuCallbackFunc func){

}

/**
 * @brief
 */
void menu_t::setTexts(string fontName, int fontSize){

}

/**
 * @brief
 */
void menu_t::setText(int index, string text){

}

/**
 * @brief
 */
void menu_t::setText(font_t* fontStyle){

}

/**
 * @brief
 */
void menu_t::setBackground(string imageName){

}

/**
 * @brief
 */
void menu_t::setBackground(image_t* image){

}

/**
 * @brief
 */
void menu_t::setImage(string imageName){

}

/**
 * @brief
 */
void menu_t::setImage(image_t* image){

}

/**
 * @brief
 */
returnVal menu_t::update(SDL_Event* event){

}

/**
 * @brief
 */
void menu_t::blit(SDL_Surface* screen){

}

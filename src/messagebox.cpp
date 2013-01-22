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

messagebox_t::messagebox_t(): nOpt(0), selIndex(0), text(NULL), box(NULL), msgPos(NULL)
{
}

messagebox_t::messagebox_t(int optNumber): nOpt(0), selIndex(0), text(NULL), box(NULL), msgPos(NULL) {
	setOpts(optNumber);
}

messagebox_t::~messagebox_t(){
	if(text != NULL){
		for(int i = 0; i <= nOpt; i++){
			if(text[i] != NULL)
				delete text[i];
		}
		delete [] text;
	}
	if(box != NULL)
		delete box;
	if(msgPos != NULL)
		delete [] msgPos;
}

void messagebox_t::setOpts(int optNumber){
	// Borramos todo antes de nada
	if(text != NULL){
		for(int i = 0; i <= nOpt; i++){
			if(text[i] != NULL)
				delete text[i];
		}
		delete [] text;
		text = NULL;
	}
	if(box != NULL){
		delete box;
		box = NULL;
	}
	if(msgPos != NULL){
		delete [] msgPos;
		msgPos = NULL;
	}

	// Esto viene siendo lo mismo de la clase menu_t
	nOpt = 0;
	selIndex = 0;

	if(optNumber > 0 && optNumber < 5){ // Como máximo 4 opciones para que quepa bien
		msgPos = new SDL_Rect[optNumber + 1]; // Reservamos uno más para el enunciado
		if(msgPos == NULL){
			fprintf(stderr, "No se ha podido reservar memoria para las posiciones de los textos del mensaje.\n");
			return;
		}

		text = new font_t*[optNumber + 1];
		if(text == NULL){
			fprintf(stderr, "No se ha podido reservar memoria para los textos del mensaje.\n");
			delete [] msgPos;
			msgPos = NULL;
			return;
		}
		for(int i = 0; i <= optNumber; i++)
			text[i] = NULL;

		nOpt = optNumber;
	}
	else
		fprintf(stderr, "No has especificado un número válido de opciones para el mensaje.\n");
}

void messagebox_t::setFont(string fontName, int fontSize){
	if(text != NULL){
		for(int i = 0; i <= nOpt; i++){
			text[i] = new font_t(fontName);
			if(text[i] != NULL){
				text[i]->setSize(fontSize);
				text[i]->setText("[UNDEFINED]");
			}
			else
				fprintf(stderr, "No se ha podido reservar memoria para la fuente nº %d.\n", i);
		}
	}
	else
		fprintf(stderr, "No se ha podido asignar una fuente al mensaje porque no se había reservado memoria para ella.\n");
}

void messagebox_t::setFont(font_t* fontStyle){
	if(text != NULL){
		for(int i = 0; i <= nOpt; i++){
			text[i] = new font_t(*fontStyle);
			if(text[i] == NULL)
				fprintf(stderr, "No se ha podido reservar memoria para la fuente nº %d.\n", i);
			else
				setText(i, "[UNDEFINED]");
		}
	}
	else
		fprintf(stderr, "No se pueden especificar las características de los textos de los menús sin haber decidido cuántos van a haber.\n");
}

void messagebox_t::setText(int index, string fontText){
	if(text != NULL && msgPos != NULL && index >= 0 && index <= nOpt){
		if(text[index] != NULL){
			text[index]->setText(fontText);
			msgPos[index].w = text[index]->width();
			msgPos[index].h = text[index]->height();
		}
		else
			fprintf(stderr, "No se puede asignar un texto al elemento %d del mensaje porque ha habido un error al asignarle propiedades.\n", index);
	}
	else
		fprintf(stderr, "No se puede asignar un texto al elemento %d del mensaje porque no se ha reservado memoria para él.\n", index);
}

void messagebox_t::setBackground(string path){
	if(box != NULL){
		delete box;
		box = NULL;
	}
	box = new image_t(path);
	if(box == NULL)
		fprintf(stderr, "Ha habido un error al crear la imagen de fondo del mensaje.\n");
}

int messagebox_t::locateTexts(){
	if(box == NULL || text == NULL || msgPos == NULL){
		fprintf(stderr, "No se pueden situar los textos porque la memoria no está reservada.\n");
		return -1;
	}

	// La posición de la ventana es en el centro
	wndPos.x = (int)((sistema->width() - box->width()) / 2);
	wndPos.y = (int)((sistema->height() - box->height()) / 2);

	// Situamos el enunciado en la mitad superior del cuadro
	msgPos[0].x = wndPos.x + (int)((box->width() / 2) - (text[0]->width() / 2));
	msgPos[0].y = wndPos.y + (int)((box->height() / 4) - (text[0]->height() / 2));

	// La distribución de los textos depende de la cantidad de ellos
	// Esto debería poder hacerse mejor
	switch(nOpt){
	case 1:
		msgPos[1].x = wndPos.x + (int)((box->width() / 2) - (text[1]->width() / 2));
		msgPos[1].y = wndPos.y + (int)((3 * box->height() / 4) - (text[1]->height() / 2));
		break;
	case 2:
		msgPos[1].x = wndPos.x + (int)((box->width() / 4) - (text[1]->width() / 2));
		msgPos[1].y = wndPos.y + (int)((3 * box->height() / 4) - (text[1]->height() / 2));
		msgPos[2].x = wndPos.x + (int)((3 * box->width() / 4) - (text[2]->width() / 2));
		msgPos[2].y = wndPos.y + (int)((3 * box->height() / 4) - (text[2]->height() / 2));
		break;
	case 3:
		msgPos[1].x = wndPos.x + (int)((box->width() / 4) - (text[1]->width() / 2));
		msgPos[1].y = wndPos.y + (int)((3 * box->height() / 4) - (text[1]->height() / 2));
		msgPos[2].x = wndPos.x + (int)((box->width() / 2) - (text[2]->width() / 2));
		msgPos[2].y = wndPos.y + (int)((3 * box->height() / 4) - (text[2]->height() / 2));
		msgPos[3].x = wndPos.x + (int)((3 * box->width() / 4) - (text[3]->width() / 2));
		msgPos[3].y = wndPos.y + (int)((3 * box->height() / 4) - (text[3]->height() / 2));
		break;
	case 4:
		msgPos[1].x = wndPos.x + (int)((box->width() / 4) - (text[1]->width() / 2));
		msgPos[1].y = wndPos.y + (int)((box->height() / 2) - (text[1]->height() / 2));
		msgPos[2].x = wndPos.x + (int)((3 * box->width() / 4) - (text[2]->width() / 2));
		msgPos[2].y = wndPos.y + (int)((box->height() / 2) - (text[2]->height() / 2));
		msgPos[3].x = wndPos.x + (int)((box->width() / 4) - (text[3]->width() / 2));
		msgPos[3].y = wndPos.y + (int)((3 * box->height() / 4) - (text[3]->height() / 2));
		msgPos[4].x = wndPos.x + (int)((3 * box->width() / 4) - (text[4]->width() / 2));
		msgPos[4].y = wndPos.y + (int)((3 * box->height() / 4) - (text[4]->height() / 2));
		break;
	}
}

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

/**
 * @brief Inicializa la clase.
 */
image_t::image_t(): img(NULL)
{
}

/**
 * @brief Inicializa la clase y carga una imagen.
 * @param path Ruta al archivo de imagen que se desea cargar.
 * @note Para este programa es preferible utilizar imágenes .png porque permiten transparencias y además este formato está bajo una licencia de software libre permisiva.
 * @see http://www.libpng.org/pub/png/src/libpng-LICENSE.txt
 */
image_t::image_t(string path): img(NULL) {
	open(path);
}

/**
 * @brief Libera el espacio ocupado por la imagen.
 */
image_t::~image_t(){
	if(img != NULL)
		SDL_FreeSurface(img);
}

/**
 * @brief Carga una imagen.
 * @param path Ruta de la imagen que se desea cargar.
 *
 * Este método intenta convertir la imagen al formato de la pantalla para que sea más rápido el proceso de blitting.
 */
void image_t::open(string path){
	string compPath = IMG_PATH;
	compPath += path;

	if(img != NULL){
		SDL_FreeSurface(img);
		img = NULL;
	}
	img = IMG_Load(compPath.c_str());
	if(img != NULL){
		SDL_Surface* temp = NULL;
		temp = SDL_DisplayFormatAlpha(img);
		if(temp != NULL){
			SDL_FreeSurface(img);
			img = temp;
		}
		else
			fprintf(stderr, "image_t::open: No se ha podido optimizar la imagen al formato de la pantalla: %s.\n", SDL_GetError());
	}
	else
		fprintf(stderr, "image_t::open: No se puede cargar la imagen \"%s\": %s.\n", compPath.c_str(), SDL_GetError());
}

/**
 * @brief Cambia la transparencia de la imagen.
 * @param alpha Nueva transparencia, entre 0 (SDL_ALPHA_TRANSPARENT) y 255(SDL_ALPHA_OPAQUE).
 */
void image_t::setAlpha(int alpha){
	if(img != NULL){
		if(alpha >= SDL_ALPHA_TRANSPARENT && alpha <= SDL_ALPHA_OPAQUE)
			SDL_SetAlpha(img, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
	}
}

/**
 * @brief Imprime la imagen en la posición indicada sobre otra superficie.
 * @param x Posición horizontal relativa al borde izquierdo de la superficie destino donde se situará el borde izquierdo de la imagen.
 * @param y Posición vertical relativa al borde superior de la superficie destino donde se situará el borde superior de la imagen.
 * @param screen Superficie destino donde se imprimirá la imagen (Normalmente la pantalla).
 * @param imZone Zona origen de la imagen que se imprimirá en la pantalla. Este valor se puede omitir para imprimir toda la imagen.
 */
void image_t::blit(int x, int y, SDL_Surface* screen, SDL_Rect* imZone){
	if(img != NULL){
		SDL_Rect dest = {(Sint16)x, (Sint16)y, 0, 0};
		SDL_BlitSurface(img, imZone, screen, &dest);
	}
}

/**
 * @brief Imprime la porción de la imagen deseada en la posición indicada sobre otra superficie.
 * @param x Posición horizontal relativa al borde izquierdo de la superficie destino donde se situará el borde izquierdo de la imagen.
 * @param y Posición vertical relativa al borde superior de la superficie destino donde se situará el borde superior de la imagen.
 * @param screen Superficie destino donde se imprimirá la imagen (Normalmente la pantalla).
 * @param imX Posición horizontal de comienzo de la imagen origen (Respecto al borde izquierdo).
 * @param imY Posición vertical de comienzo de la imagen origen (Respecto al borde superior).
 * @param imW Anchura de la imagen.
 * @param imH Altura de la imagen.
 */
void image_t::blit(int x, int y, SDL_Surface* screen, int imX, int imY, int imW, int imH){
	if(img != NULL){
		SDL_Rect dest = {(Sint16)x, (Sint16)y, 0, 0};
		if(imX < 0) imX = -imX;
		if(imY < 0) imY = -imY;
		if(imW < 0) imW = -imW;
		if(imH < 0) imH = -imH;
		SDL_Rect src = {(Sint16)imX, (Sint16)imY, (Uint16)imW, (Uint16)imH};
		SDL_BlitSurface(img, &src, screen, &dest);
	}
	else
		fprintf(stderr, "image_t::blit: No se puede imprimir por pantalla porque no se ha cargado.\n");
}

/**
 * @return Anchura de la imagen completa.
 */
int image_t::width(){
	return img != NULL? img->w : 0;
}

/**
 * @return Altura de la imagen completa.
 */
int image_t::height(){
	return img != NULL? img->h : 0;
}

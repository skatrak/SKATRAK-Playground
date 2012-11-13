#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../include/image.hpp"

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
	load(path);
}

/**
 * @brief Libera el espacio ocupado por la clase.
 */
image_t::~image_t(){
	if(img != NULL)
		SDL_FreeSurface(img);
}

/**
 * @brief Carga una imagen
 * @param path Ruta de la imagen que se desea cargar.
 *
 * Este método intenta convertir la imagen al formato de la pantalla para que sea más rápido el proceso de blitting.
 */
void image_t::load(string path){
	if(img != NULL){
		SDL_FreeSurface(img);
		img = NULL;
	}
	img = IMG_Load(path.c_str());
	if(img != NULL){
		SDL_Surface* temp = NULL;
		temp = SDL_DisplayFormatAlpha(img);
		if(temp != NULL){
			SDL_FreeSurface(img);
			img = temp;
		}
		else
			fprintf(stderr, "No se ha podido optimizar la imagen al formato de la pantalla.\n");
	}
	else
		fprintf(stderr, "No se puede cargar la imagen \"%s\".\n", path.c_str());
}

/**
 * @brief Imprime la imagen en la posición indicada sobre otra superficie.
 * @param x Posición horizontal relativa al borde izquierdo de la superficie destino donde se situará el borde izquierdo de la imagen.
 * @param y Posición vertical relativa al borde superior de la superficie destino donde se situará el borde superior de la imagen.
 * @param screen Superficie destino donde se imprimirá la imagen (Normalmente la pantalla).
 * @param imZone Zona origen de la imagen que se imprimirá en la pantalla. Este valor se puede omitir para imprimir toda la imagen.
 * @note Esta función está sobrecargada.
 */
void image_t::blit(int x, int y, SDL_Surface* screen, SDL_Rect* imZone){
	if(img != NULL){
		SDL_Rect dest = {x, y, 0, 0};
		SDL_BlitSurface(img, imZone, screen, &dest);
	}
	else
		fprintf(stderr, "No se puede imprimir la imagen por pantalla porque no se ha cargado.\n");
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
		SDL_Rect dest = {x, y, 0, 0};
		if(imX < 0) imX = -imX;
		if(imY < 0) imY = -imY;
		if(imW < 0) imW = -imW;
		if(imH < 0) imH = -imH;
		SDL_Rect src = {imX, imY, imW, imH};
		SDL_BlitSurface(img, &src, screen, &dest);
	}
	else
		fprintf(stderr, "No se puede imprimir la imagen por pantalla porque no se ha cargado.\n");
}

/**
 * @return Anchura de la imagen completa.
 */
int image_t::width(){
	if(img != NULL) return img->w;
	else return 0;
}

/**
 * @return Altura de la imagen completa.
 */
int image_t::height(){
	if(img != NULL) return img->h;
	else return 0;
}

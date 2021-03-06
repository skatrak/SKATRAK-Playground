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

/* Inclusi�n de cabeceras necesarias */
// Cabecera de la clase
#include "font.hpp"
// Est�ndar
#include <string>
using std::string;
// SDL
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
// Propias
#include "SKATRAK_PLAYGROUND.hpp"
#include "system.hpp"

/**
 * @brief Constructor. Inicializa los valores de las variables e inicia SDL_TTF si no se ha iniciado.
 */
font_t::font_t(): font(NULL), rendered(NULL), fontName(""), fontSize(DEFAULT_FONT_SIZE), fontStyle(DEFAULT_FONT_STYLE), fontText(""), fontAlpha(SDL_ALPHA_OPAQUE), changed(true) {
	sistema->initSubsystems(SYS_SUBST_TTF);
	setColor(0, 0, 0);
}

/**
 * @brief Constructor de copia. Inicializa los valores de las variables e inicia SDL_TTF si no se ha iniciado.
 * @param copy Instancia de font_t que se desea copiar.
 */
font_t::font_t(font_t& copy): font(NULL), rendered(NULL), fontName(""), fontSize(copy.fontSize), fontStyle(copy.fontStyle), fontText(""), fontAlpha(SDL_ALPHA_OPAQUE), changed(true) {
	if(sistema->initSubsystems(SYS_SUBST_TTF) & SYS_SUBST_TTF)
		open(copy.fontName);
	fontColor = copy.fontColor;
}

/**
 * @brief Constructor. Inicializa los valores de las variables e inicia SDL_TTF si no se ha iniciado.
 * @param path Ruta del archivo de fuentes .ttf o .fon que contiene la fuente a utilizar.
 */
font_t::font_t(string path): font(NULL), rendered(NULL), fontName(path), fontSize(DEFAULT_FONT_SIZE), fontStyle(DEFAULT_FONT_STYLE), fontText(""), fontAlpha(SDL_ALPHA_OPAQUE), changed(true) {
	if(sistema->initSubsystems(SYS_SUBST_TTF) & SYS_SUBST_TTF)
		open(path);
	setColor(0, 0, 0);
}

/**
 * @brief Destructor. Libera la memoria reservada.
 */
font_t::~font_t(){
	if(font != NULL)
		TTF_CloseFont(font);
	if(rendered != NULL)
		SDL_FreeSurface(rendered);
}

/**
 * @brief Abre un archivo de fuentes .ttf o .fon.
 */
void font_t::open(string path){
	fontName = FONT_PATH;
	fontName += path;

	if(font != NULL){
		TTF_CloseFont(font);
		font = NULL;
	}
	font = TTF_OpenFont(fontName.c_str(), fontSize);
	if(font == NULL)
		fprintf(stderr, "font_t::open: No se ha podido abrir \"%s\": %s.\n", fontName.c_str(), TTF_GetError());
	changed = true;
	fontName = path;	// Hay que resetear la variable, porque si no se va a�adiendo FONT_PATH al principio todo el rato
}

/**
 * @brief Cambia el tama�o de la fuente cargada. Se puede utilizar antes de cargar la fuente tambi�n.
 * @param size Tama�o de la fuente.
 */
void font_t::setSize(int size){
	if(size != fontSize){
		changed = true;
		fontSize = size;
		open(fontName);
	}
}

/**
 * @brief Cambia el estilo de la fuente.
 * @param style M�scara de bits que especifica las propiedades del estilo.
 *
 * Las posibles m�scaras son:
 * TTF_STYLE_BOLD,
 * TTF_STYLE_ITALIC,
 * TTF_STYLE_UNDERLINE,
 * TTF_STYLE_STRIKETHROUGH,
 * TTF_STYLE_NORMAL
 */
void font_t::setStyle(int style){
	if(style != fontStyle){
		changed = true;
		fontStyle = style;
	}
}

/**
 * @brief Especifica el texto que se desea renderizar.
 * @param text Texto a renderizar.
 */
void font_t::setText(string text){
	if(text != fontText){
		changed = true;
		fontText = text;
	}
}

/**
 * @brief Cambia el color de la fuente.
 * @param R Valor entre 0 y 255 que representa la cantidad de Rojo que se desea.
 * @param G Valor entre 0 y 255 que representa la cantidad de Verde que se desea.
 * @param B Valor entre 0 y 255 que representa la cantidad de Azul que se desea.
 */
void font_t::setColor(int R, int G, int B){
	if(fontColor.r != R || fontColor.g != G || fontColor.b != B){
		changed = true;
		fontColor.r = R;
		fontColor.g = G;
		fontColor.b = B;
	}
}

/**
 * @brief Cambia la transparencia de la fuente al imprimirla por pantalla.
 * @param alpha Valor de transparencia que se desea poner. Debe estar entre 0 (SDL_ALPHA_TRANSPARENT) y 255 (SDL_ALPHA_OPAQUE).
 */
void font_t::setAlpha(int alpha){
	if(alpha >= SDL_ALPHA_TRANSPARENT && alpha <= SDL_ALPHA_OPAQUE && alpha != fontAlpha){
		fontAlpha = alpha;
		changed = true;
	}
}

/**
 * @brief Imprime la fuente por la pantalla
 * @param x Posici�n X donde se imprime
 * @param y Posici�n Y donde se imprime
 * @param screen Superficie sobre la que se har� el blitting.
 */
void font_t::blit(int x, int y, SDL_Surface* screen){
	if(font != NULL){
		if(changed){
			TTF_SetFontStyle(font, fontStyle);
			if(rendered != NULL){
				SDL_FreeSurface(rendered);
				rendered = NULL;
			}
			if(fontAlpha == SDL_ALPHA_OPAQUE){
				rendered = TTF_RenderText_Blended(font, fontText.c_str(), fontColor);
				if(rendered == NULL)
					fprintf(stderr, "font_t::blit: No se ha podido renderizar: %s.\n", TTF_GetError());
			}
			else {
				rendered = TTF_RenderText_Solid(font, fontText.c_str(), fontColor);
				if(rendered == NULL)
					fprintf(stderr, "font_t::blit: No se ha podido renderizar: %s.\n", TTF_GetError());
				else
					SDL_SetAlpha(rendered, SDL_SRCALPHA | SDL_RLEACCEL, fontAlpha);
			}
			if(rendered != NULL){
				changed = false;
				SDL_Surface* temp = NULL;
				temp = SDL_DisplayFormatAlpha(rendered);
				if(temp == NULL)
					fprintf(stderr, "font_t::blit: No se ha podido optimizar el formato: %s.\n", SDL_GetError());
				else {
					SDL_FreeSurface(rendered);
					rendered = temp;
				}
			}
		}
		int tmp = 0;
		TTF_GlyphMetrics(font, 'l', NULL, NULL, NULL, &tmp, NULL);
		SDL_Rect dest = {(Sint16)x, (Sint16)(y - TTF_FontAscent(font) + tmp), 0, 0};
		SDL_BlitSurface(rendered, NULL, screen, &dest);
	}
}

/**
 * @return Anchura en p�xeles del texto cargado actualmente con la fuente actual.
 */
int font_t::width(){
	if(font == NULL)
		return 0;
	int retVal = 0;
	TTF_SizeText(font, fontText.c_str(), &retVal, NULL);
	return retVal;
}

/**
 * @return Altura en p�xeles m�xima que puede alcanzar la fuente actual.
 */
int font_t::height(){
	if(font == NULL)
		return 0;

	int miny = 0, maxy = 0;
	// Hago este truco porque usando las medidas por defecto de las fuentes quedan poco ajustadas
	TTF_GlyphMetrics(font, 'l', NULL, NULL, NULL, &maxy, NULL); // Una letra larga por arriba
	TTF_GlyphMetrics(font, 'p', NULL, NULL, &miny, NULL, NULL); // Una letra larga por abajo
	return maxy - miny;
}

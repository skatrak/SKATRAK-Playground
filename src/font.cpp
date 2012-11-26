#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../include/font.hpp"

/**
 * @brief Constructor. Inicializa los valores de las variables e inicia SDL_TTF si no se ha iniciado.
 */
font_t::font_t(): font(NULL), rendered(NULL), fontSize(DEFAULT_FONT_SIZE), fontStyle(DEFAULT_FONT_STYLE), fontText(""), changed(true)
{
	if(!TTF_WasInit()){
		if(TTF_Init() < 0)
			fprintf(stderr, "No se ha podido inicializar SDL_TTF.\n");
	}
}

/**
 * @brief Constructor. Inicializa los valores de las variables e inicia SDL_TTF si no se ha iniciado.
 * @param fontname Ruta del archivo de fuentes .ttf o .fon que contiene la fuente a utilizar.
 */
font_t::font_t(string fontname): font(NULL), rendered(NULL), fontSize(DEFAULT_FONT_SIZE), fontStyle(DEFAULT_FONT_STYLE), fontText(""), changed(true)
{
	if(!TTF_WasInit()){
		if(TTF_Init() < 0)
			fprintf(stderr, "No se ha podido inicializar SDL_TTF.\n");
	}
	open(fontname);
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
void font_t::open(string fontname){
	if(font != NULL){
		TTF_CloseFont(font);
		font = NULL;
	}
	font = TTF_OpenFont(fontname.c_str(), fontSize);
	if(fontname == NULL)
		fprintf(stderr, "No se ha podido abrir la fuente \"%s\".\n", fontname.c_str());
	changed = true;
}

/**
 *
 */
void font_t::setSize(int size){
	if(size != fontSize){
		changed = true;
		fontSize = size;
	}
}

/**
 *
 */
void font_t::setStyle(int style){
	if(style != fontStyle){
		changed = true;
		fontStyle = style;
	}
}

/**
 *
 */
void font_t::setText(string text){
	if(text != fontText){
		changed = true;
		fontText = text;
	}
}

/**
 *
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
 *
 */
void font_t::blit(int x, int y, SDL_Surface* screen){
	if(font != NULL){
		if(changed){
			TTF_SetFontStyle(font, fontStyle);
			if(rendered != NULL){
				SDL_FreeSurface(rendered);
				rendered = NULL;
			}
			rendered = TTF_RenderTextBlended(font, fontText.c_str(), fontColor);
			if(rendered == NULL)
				fprintf(stderr, "No se ha podido renderizar la fuente.\n");
			else {
				changed = false;
				SDL_Surface* temp = NULL;
				temp = SDL_DisplayFormatAlpha(rendered);
				if(temp == NULL)
					fprintf(stderr, "No se ha podido optimizar el formato de la fuente.\n");
				else {
					SDL_FreeSurface(rendered);
					rendered = temp;
				}
				SDL_Rect dest = {x, y, 0, 0};
				SDL_BlitSurface(rendered, NULL, screen, &dest);
			}
		}
	}
	else
		fprintf(stderr, "No se puede imprimir la fuente por la pantalla porque no se ha cargado.\n");
}
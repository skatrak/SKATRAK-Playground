#ifndef __SYSTEM_T__
#define __SYSTEM_T__

/**
 * @class system_t
 * @brief Representa todo lo necesario para inicializar y cerrar SDL.
 * @note Sólo se puede tener un objeto de este tipo al mismo tiempo en un programa.
 */
class system_t {
	private:
		SDL_Surface* screen;
		int width;
		int height;
		int bpp;
		bool fullscr;
	public:
	system_t(int scr_w, int scr_h, int depth);
	~system_t();
	void toggleFullscreen();
	int w(){ return width; }
	int h(){ return height; }
	SDL_Surface* scr(){ return screen; }
	void update();
};

/**
 * @fn system_t::w
 * @return Devuelve la anchura de la pantalla creada por SDL.
 */

/**
 * @fn system_t::h
 * @return Devuelve la altura de la pantalla creada por SDL.
 */

/**
 * @fn system_t::scr
 * @return Devuelve un puntero a la SDL_Surface que apunta a la pantalla de SDL.
 */

#include "../src/system.cpp"

#endif

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
		SDL_Surface* wIcon;
		int screenWidth;
		int screenHeight;
		int bpp;
		bool fullscr;
	public:
	system_t(int scr_w, int scr_h, int depth);
	~system_t();
	void toggleFullscreen();
	void setIcon(string iconpath);
	int width(){ return screenWidth; }
	int height(){ return screenHeight; }
	SDL_Surface* scr(){ return screen; }
	void update();
};

/**
 * @fn system_t::width
 * @return Devuelve la anchura de la pantalla creada por SDL.
 */

/**
 * @fn system_t::height
 * @return Devuelve la altura de la pantalla creada por SDL.
 */

/**
 * @fn system_t::scr
 * @return Devuelve un puntero a la SDL_Surface que apunta a la pantalla de SDL.
 */

#endif

/**
 * @brief Crea la clase sistema e inicializa las propiedades de la pantalla. También inicializa SDL.
 * @param scr_w Anchura de la pantalla.
 * @param scr_h Altura de la pantalla.
 * @param depth Profundidad de bits de la pantalla.
 * @note En el caso de que la pantalla no se pudiera iniciar con las opciones especificadas, imprimirá un mensaje de error.
 */
system_t::system_t(int scr_w, int scr_h, int depth): width(scr_w), height(scr_h), bpp(depth), screen(NULL)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(width, height, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL)
		fprintf(stderr, "No se ha podido iniciar el modo de video %dx%d a %d bits.\n", width, height, bpp);
}

/**
 * @brief Destructor. Libera la memoria ocupada por la pantalla y cierra SDL.
 */
system_t::~system_t(){
	if(screen != NULL)
		SDL_FreeSurface(screen);
	SDL_Quit();
}

/**
 * @brief Intercambia entre pantalla completa y ventana.
*/
void system_t::toggleFullscreen(){
	fullscr? fullscr = false : fullscr = true;
	if(screen != NULL){
		SDL_FreeSurface(screen);
		screen = NULL;
	}
	if(fullscr){
		screen = SDL_SetVideoMode(width, height, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
		if(screen == NULL)
			fprintf(stderr, "No se ha podido iniciar el modo de video %dx%d a %d bits con pantalla completa.\n", width, height, bpp);
	} else {
		screen = SDL_SetVideoMode(width, height, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);
		if(screen == NULL)
			fprintf(stderr, "No se ha podido iniciar el modo de video %dx%d a %d bits sin pantalla completa.\n", width, height, bpp);
	}
}

/**
 * @brief Actualiza la pantalla.
 * @note Es necesario llamar esta función para que se intercambien los buffers de vídeo.
*/
void system_t::update(){
	if(screen != NULL)
		SDL_Flip(screen);
	else
		fprintf(stderr, "No se ha podido mostrar la pantalla.\n");
}

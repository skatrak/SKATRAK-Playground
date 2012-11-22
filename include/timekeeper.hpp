#ifndef __TIMEKEEPER_T__
#define __TIMEKEEPER_T__

/**
 * @class timekeeper_t
 * @brief Temporizador para controlar la velocidad de ejecución del programa y la cantidad de fotogramas que se van renderizando.
 */
class timekeeper_t {
	private:
		int start;
		int current;
		int frames;
	public:
		timekeeper_t(): current(0), frames(0) { start = SDL_GetTicks(); }
		void refresh();
		int elapsed();
		void waitFramerate(int fps);
		int renderedFrames();
};

/**
 * @fn timekeeper_t::timekeeper_t
 * @brief Constructor. Inicializa el reloj con el tiempo inicial.
 */

#endif


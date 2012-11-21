#ifndef __TIMER_T__
#define __TIMER_T__

/**
 * @class timer_t
 * @brief Temporizador para controlar la velocidad de ejecución del programa y la cantidad de fotogramas que se van renderizando.
 */
class timer_t {
	private:
		int start;
		int current;
		int frames;
	public:
		timer_t(): start(0), current(0), frames(0) {}
		void start();
		int elapsed();
		void waitFramerate(int fps);
		int renderedFrames();
};

#endif
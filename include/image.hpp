#ifndef __IMAGE_T__
#define __IMAGE_T__

/**
 * @class image_t
 * @brief Clase encargada de representar las imágenes que se utilizan en el programa.
 */
class image_t {
	private:
		SDL_Surface* img;
	public:
		image_t();
		image_t(string path);
		~image_t();
		void open(string path);
		void blit(int x, int y, SDL_Surface* screen, SDL_Rect* imZone = NULL);
		void blit(int x, int y, SDL_Surface* screen, int imX, int imY, int imW, int imH);
		int width();
		int height();
};

#endif

#ifndef __FONT_T__
#define __FONT_T__

const int DEFAULT_FONT_SIZE = 24;
const int DEFAULT_FONT_STYLE = TTF_STYLE_NORMAL;

/**
 * @class font_t
 * @brief Clase que representa una fuente True-Type que se puede imprimir gráficamente por pantalla.
 */
class font_t {
	private:
		TTF_Font* font;
		SDL_Surface* rendered;
		string fontName;
		int fontSize;
		int fontStyle;
		string fontText;
		SDL_Color fontColor;
		bool changed;
	public:
		font_t();
		font_t(string path);
		~font_t();
		void open(string path);
		void setSize(int size);
		void setStyle(int style);
		void setText(string text);
		void setColor(int R, int G, int B);
		void blit(int x, int y, SDL_Surface* screen);
		int width();
		int height();
		int size(){ return fontSize; }
};

/**
 * @fn font_t::size
 * @return Valor del tamaño de la fuente.
 */

#endif

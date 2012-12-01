#ifndef __SFX_T__
#define __SFX_T__

const int DEFAULT_SFX_VOLUME = 128;

/**
 * @class sfx_t
 * @brief Representa un efecto de sonido, que se reproduce una sola vez cuando se le indica.
 * @note Como la clase music_t ya inicializa SDL, no hay que hacerlo para cada efecto de sonido.
 * Suponemos que hay una cantidad suficiente de canales de audio reservados.
 */
class sfx_t {
	private:
		Mix_Chunk* sound;
		int volume;
	public:
		sfx_t();
		sfx_t(string path);
		~sfx_t();
		void setSound(string path);
		void setVol(int vol);
		void play();
		int vol(){ return volume; }
};

/**
 * @fn sfx_t::vol
 * @return Volumen actual del efecto de sonido.
 */

#endif

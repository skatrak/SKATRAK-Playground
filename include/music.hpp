#ifndef __MUSIC_T__
#define __MUSIC_T__

using std::string;

const int FADEIN_DELAY = 1000;

/**
 * @class music_t
 * @brief Clase cuyo objetivo es tener una lista de reproducción de música con la cantidad que se necesite de canciones que se pueda manipular
 * fácilmente.
 * @note Sólo se puede tener un objeto de este tipo en tu programa.
 */
class music_t {
	private:
		Mix_Music** music;
		string* music_names;
		int n_tracks;
		int volume;
		int current;
		bool running, playing, paused;
	public:
		music_t();
		music_t(int nT);
		~music_t();
		void setTracks(int n);
		void setTrack(int index, string name);
		void play();
		void pause();
		void halt();
		void setVol(int vol);
		friend void nextTrack();
};

#include "../src/music.cpp"

#endif

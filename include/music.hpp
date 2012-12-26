/*
 *  This file is part of SKATRAK Playground.
 *
 *  SKATRAK Playground is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/> or
 *  write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 *  Floor, Boston, MA 02110-1301 USA
 *
 *  Sergio M. Afonso Fumero <theSkatrak@gmail.com>
 */

#ifndef __MUSIC_T__
#define __MUSIC_T__

const int FADEIN_DELAY = 1000;
const int MAX_VOLUME = 128;
const int AUDIO_CHANNELS = 10;

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
		music_t(void);
		music_t(int nT);
		~music_t(void);
		void setTracks(int n);
		void setTrack(int index, string path);
		void play(void);
		void pause(void);
		void halt(void);
		void setVol(int vol);
		friend void nextTrack(void);
};

#endif

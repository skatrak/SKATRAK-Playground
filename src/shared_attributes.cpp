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

/* Inclusión de cabeceras necesarias */
#include "shared_attributes.hpp"
// Estándar
#include <string>
using std::string;
// Propias
#include "SKATRAK_PLAYGROUND.hpp"
#include "inifile.hpp"
#include "music.hpp"

/**
 * @brief Carga en el archivo .ini con el nombre especificado la información de la lista de reproducción.
 * @param path Nombre del archivo .ini con la configuración.
 * @return '0' En caso de éxito y '< 0' si hay errores.
 */
int loadTracklist(string path){
	inifile_t settings(path);
	if(settings.errorStatus()){
		fprintf(stderr, "loadTracklist: %s\n", settings.errorString().c_str());
		return -1;
	}
	int volumen = settings.readInt("Setlist", "Volumen");
	if(settings.errorStatus()){
		fprintf(stderr, "loadTracklist: %s\n", settings.errorString().c_str());
		return -1;
	}
	int nPistas = settings.readInt("Setlist", "Pistas");
	if(settings.errorStatus()){
		fprintf(stderr, "loadTracklist: %s\n", settings.errorString().c_str());
		return -1;
	}

	musica->setVol(volumen);
	musica->setTracks(nPistas);

	char nombrePista[10];
	for(int i = 0; i < nPistas; ++i){
		sprintf(nombrePista, "Pista%d", i+1);
		musica->setTrack(i, settings.readString("Setlist", nombrePista));
	}
	musica->play();
	return 0;
}

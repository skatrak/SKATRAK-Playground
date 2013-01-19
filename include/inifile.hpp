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

#ifndef __INIFILE_T__
#define __INIFILE_T__

using std::ifstream;

/* Enumeración con los distintos tipos de error que pueden suceder al leer un fichero .ini */
enum iniError {
	NOERROR = 0,	// No problemo
	FILENOFOUND,	// Se ha intentado abrir un archivo inexistente
	NOTOPENED,		// Se ha intentado acceder a datos sin abrir ningún archivo
	WRONGTYPE,		// Se ha intentado leer una variable de un tipo distinto
	NOEXISTVAR,		// La variable con el nombre especificado no existe en la sección especificada
	NOEXISTSECTION	// La sección especificada no existe
};

/**
 * @class inifile_t
 * @brief Clase para gestionar información guardada en un fichero .ini
 */
class inifile_t {
	private:
		ifstream input;
		iniError error;
	public:
		inifile_t(void);
		inifile_t(string path);
		~inifile_t(void);
		void open(string path);
		int readInt(string section, string varName);
		double readDouble(string section, string varName);
		string readString(string section, string varName);
		bool readBool(string section, string varName);
		iniError errorStatus(void){ return error; }
		void resetError(void){ error = NOERROR; }
};

/**
 * @fn inifile_t::errorStatus
 * @brief Devuelve el estado de la última operación realizada.
 * @return Uno de los valores de iniError.
 *
 * NOERROR está definida como 0, lo que permite escribir cosas como:
 * if(archivoIni.errorStatus()){ // Comprobar errores... }
 */

/**
 * @fn inifile_t::resetError
 * @brief Devuelve el estado de error a 'sin errores'
 */

#endif

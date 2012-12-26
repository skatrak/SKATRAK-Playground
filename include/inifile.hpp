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

/**
 * @class inifile_t
 * @brief Clase para gestionar información guardada en un fichero .ini
 */
class inifile_t {
	private:
		ifstream input;
		bool error;
	public:
		inifile_t(void);
		inifile_t(string path);
		~inifile_t(void);
		void open(string path);
		int readInt(string section, string varName);
		double readDouble(string section, string varName);
		string readString(string section, string varName);
		bool readBool(string section, string varName);
		bool errorStatus(void){ return error; }
};

/**
 * @fn inifile_t::errorStatus
 * @brief Devuelve el estado de la última operación realizada.
 * @return 1 en caso de error y 0 en otro caso.
 */

#endif

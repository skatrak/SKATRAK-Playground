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
// Cabecera de la clase
#include "inifile.hpp"
// Estándar
#include <string>
#include <fstream>
using std::string;
using std::ifstream;
// Propias
#include "SKATRAK_PLAYGROUND.hpp"
#include "str_operations.hpp"

/**
 * @brief Constructor. Inicialización de variables.
 */
inifile_t::inifile_t(): error(NOERROR)
{
}

/**
 * @brief Constructor. Inicializa variables y abre un fichero .ini
 * @param path Ruta del fichero .ini a abrir.
 * @note La extensión del fichero no tiene por qué ser '.ini', pero se recomienda que sea así.
 */
inifile_t::inifile_t(string path): error(NOERROR) {
	open(path);
}

/**
 * @brief Destructor. Cierra el fichero asociado.
 */
inifile_t::~inifile_t(){
	if(input.is_open())
		input.close();
}

/**
 * @brief Abre un fichero para la lectura de los datos.
 * @param path Ruta del fichero .ini a abrir.
 */
void inifile_t::open(string path){
	string compPath = INI_PATH;
	compPath += path;

	if(input.is_open())
		input.close();
	input.open(compPath.c_str());
	if(input.is_open())
		error = NOERROR;
	else {
		fprintf(stderr, "inifile_t::open: No se ha podido abrir \"%s\".\n", compPath.c_str());
		error = FILENOFOUND;
	}
}

/**
 * @brief Lee un entero guardado en una variable en el archivo .ini.
 * @param section Nombre de la sección donde está guardada la variable. No se debe poner entre corchetes.
 * @param varName Nombre de la variable a buscar en el archivo.
 * @return El valor de la variable o '0' si hubo un error.
 * @note Si devuelve el valor '0', utilizar errorStatus para decidir si fue un error o la variable tiene ese valor.
 */
int inifile_t::readInt(string section, string varName){
	// Comprobamos que haya un archivo cargado correctamente
	if(!input.is_open()){
		fprintf(stderr, "inifile_t::readInt: No se ha abierto un archivo, así que no se pueden leer valores.\n");
		error = NOTOPENED;
		return 0;
	}
	// Leemos el contenido de la variable y lo traducimos a entero
	string content = readString(section, varName);
	int value = str_op::strtoint(content.c_str());
	// Comprobamos que la lectura haya sido correcta y devolvemos el resultado
	if(value != ERROR_INT_VAL){
		error = NOERROR;
		return value;
	}
	else {
		fprintf(stderr, "inifile_t::readInt: El contenido de la variable \"%s\" no es un entero.\n", varName.c_str());
		error = WRONGTYPE;
		return 0;
	}
}

/**
 * @brief Lee un flotante de doble precisión guardado en una variable en el archivo .ini.
 * @param section Nombre de la sección donde está guardada la variable. No se debe poner entre corchetes.
 * @param varName Nombre de la variable a buscar en el archivo.
 * @return El valor de la variable o '0' si hubo un error.
 * @note Si devuelve el valor '0', utilizar errorStatus para decidir si fue un error o la variable tiene ese valor.
 */
double inifile_t::readDouble(string section, string varName){
	// Comprobamos que haya un archivo cargado correctamente
	if(!input.is_open()){
		fprintf(stderr, "inifile_t::readDouble: No se ha abierto un archivo, así que no se pueden leer valores.\n");
		error = NOTOPENED;
		return 0.0;
	}
	// Leemos el contenido de la variable y lo traducimos a flotante
	string content = readString(section, varName);
	double value = str_op::strtodouble(content.c_str());
	// Comprobamos que la lectura haya sido correcta y devolvemos el resultado
	if(value != ERROR_DOUBLE_VAL){
		error = NOERROR;
		return value;
	}
	else {
		fprintf(stderr, "inifile_t::readDouble: El contenido de la variable \"%s\" no es un número decimal.\n", varName.c_str());
		error = WRONGTYPE;
		return ERROR_DOUBLE_VAL;
	}
}

/**
 * @brief Lee una cadena de caracteres guardada en una variable en el archivo .ini.
 * @param section Nombre de la sección donde está guardada la variable. No se debe poner entre corchetes.
 * @param varName Nombre de la variable a buscar en el archivo.
 * @return El valor de la variable o la cadena vacía si hubo un error.
 * @note Si devuelve la cadena vacía, utilizar errorStatus para decidir si fue un error o la variable tiene ese valor.
 */
string inifile_t::readString(string section, string varName){
	// Comprobamos que haya un archivo cargado correctamente
	if(!input.is_open()){
		fprintf(stderr, "inifile_t::readString: No se ha abierto un archivo, así que no se pueden leer valores.\n");
		error = NOTOPENED;
		return "";
	}

	int i;
	string temp = "";	// Esta variable va leyendo cada línea del fichero
	string temp2 = "[";
	temp2 += section;	// temp2 = "[SECCION]"
	temp2 += "]";

	// Recolocamos el puntero de lectura al principio del fichero
	input.seekg(std::ios::beg);
	while(!input.eof()){
		// Buscamos la sección
		getline(input, temp);
		if(temp2 == temp){
			temp2 = varName;	// temp2 = NombreDeLaVariable
			while(!input.eof()){
				temp = "";
				getline(input, temp);
				// Comprobamos que no hemos pasado de sección
				if(temp[0] != '['){
					// Comprobamos que no sea un comentario
					if(temp[0] != '#'){
						// Nos situamos en el primer '=' de la cadena (o al final si no hay ninguno)
						for(i = 0; temp[i] != '=' && temp[i] != '\0'; i++);
						// Comprobamos que tiene contenido
						if(temp[i] != '\0'){
							// Comprobamos que las variables tienen el mismo nombre
							if(strncmp(temp.c_str(), temp2.c_str(), i) == 0){
								// Borramos la cadena desde el principio hasta el '=' incluído
								temp.erase(0, i+1);
								error = NOERROR;
								// Devolvemos el valor interpretado
								return temp;
							}
							// Si no tienen el mismo nombre, seguimos buscando
						}
						// No sabemos qué es esto, así que seguimos buscando
					}
					// Si es un comentario seguimos buscando
				}
				// Como nos hemos pasado de sección, quiere decir que la variable no existe en esa sección
				else {
					fprintf(stderr, "inifile_t::readString: No se encuentra la variable \"%s\" en la sección \"[%s]\" en el archivo.\n", varName.c_str(), section.c_str());
					error = NOEXISTVAR;
					return "";
				}
			}
		}
		temp = "";
	}
	fprintf(stderr, "inifile_t::readString: No se encuentra la sección \"[%s]\" en el archivo.\n", section.c_str());
	error = NOEXISTSECTION;
	return "";
}

/**
 * @brief Lee un booleano guardado en una variable en el archivo .ini.
 * @param section Nombre de la sección donde está guardada la variable. No se debe poner entre corchetes.
 * @param varName Nombre de la variable a buscar en el archivo.
 * @return El valor de la variable o 'false' si hubo un error.
 * @note Si devuelve el valor 'false', utilizar errorStatus para decidir si fue un error o la variable tiene ese valor.
 */
bool inifile_t::readBool(string section, string varName){
	string temp = readString(section, varName);
	if(strcasecmp(temp.c_str(), "true") == 0 || strcasecmp(temp.c_str(), "1") == 0){
		error = NOERROR;
		return true;
	}
	if(strcasecmp(temp.c_str(), "false") == 0 || strcasecmp(temp.c_str(), "0") == 0){
		error = NOERROR;
		return false;
	}
	fprintf(stderr, "inifile_t::readBool: El contenido de la variable \"%s\" no es un valor booleano.\n", varName.c_str());
	error = WRONGTYPE;
	return false;
}

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

#include "../include/SKATRAK_PLAYGROUND.hpp"
#include "../include/str_operations.hpp"

/**
 * @brief Constructor. Inicialización de variables.
 */
inifile_t::inifile_t(): error(false)
{
}

/**
 * @brief Constructor. Inicializa variables y abre un fichero .ini
 * @param path Ruta del fichero .ini a abrir.
 * @note La extensión del fichero no tiene por qué ser '.ini', pero se recomienda que sea así.
 */
inifile_t::inifile_t(string path): error(false) {
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
		error = false;
	else {
		fprintf(stderr, "No se ha podido abrir el fichero .ini \"%s\".\n", compPath.c_str());
		error = true;
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
		fprintf(stderr, "No se ha abierto un archivo '.ini', así que no se pueden leer valores.\n");
		error = true;
		return 0;
	}

	int i;
	string temp = "";	// Esta variable va leyendo cada línea del fichero.
	string temp2 = "[";
	temp2 += section;	// temp2 = "[SECCION]"
	temp2 += "]";

	input.seekg(std::ios::beg);
	while(!input.eof()){
		getline(input, temp);
		// Buscamos la sección
		if(temp2 == temp){
			temp2 = varName;
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
								// Devolvemos el valor interpretado
								int tmp = str_op::strtoint(temp.c_str());
								if(tmp != ERROR_INT_VAL){
									error = false;
									return tmp;
								}
								else {
									fprintf(stderr, "El contenido de la variable \"%s\" no es un entero.\n", varName.c_str());
									error = true;
									return 0;
								}
							}
							// Si no tienen el mismo nombre, seguimos buscando
						}
						// No sabemos qué es esto, así que seguimos buscando
					}
					// Si es un comentario seguimos buscando
				}
				// Como nos hemos pasado de sección, quiere decir que la variable no existe en esa sección
				else {
					fprintf(stderr, "No se encuentra la variable \"%s\" en la sección \"[%s]\" en el archivo .ini.\n", varName.c_str(), section.c_str());
					error = true;
					return 0;
				}
			}
		}
		temp = "";
	}
	fprintf(stderr, "No se encuentra la sección \"[%s]\" en el archivo .ini.\n", section.c_str());
	error = true;
	return 0;
}

/**
 * @brief Lee un flotante de doble precisión guardado en una variable en el archivo .ini.
 * @param section Nombre de la sección donde está guardada la variable. No se debe poner entre corchetes.
 * @param varName Nombre de la variable a buscar en el archivo.
 * @return El valor de la variable o '0' si hubo un error.
 * @note Si devuelve el valor '0', utilizar errorStatus para decidir si fue un error o la variable tiene ese valor.
 */
double inifile_t::readDouble(string section, string varName){
	if(!input.is_open()){
		fprintf(stderr, "No se ha abierto un archivo '.ini', así que no se pueden leer valores.\n");
		error = true;
		return 0.0;
	}

	int i;
	string temp = "";
	string temp2 = "[";
	temp2 += section;
	temp2 += "]";

	input.seekg(std::ios::beg);
	while(!input.eof()){
		getline(input, temp);
		if(temp2 == temp){
			temp2 = varName;
			while(!input.eof()){
				temp = "";
				getline(input, temp);
				if(temp[0] != '['){
					if(temp[0] != '#'){
						for(i = 0; temp[i] != '=' && temp[i] != '\0'; i++);
						if(temp[i] != '\0'){
							if(strncmp(temp.c_str(), temp2.c_str(), i) == 0){
								temp.erase(0, i+1);
								double tmp = str_op::strtodouble(temp.c_str());
								if(tmp != (double)ERROR_INT_VAL){
									error = false;
									return tmp;
								}
								else {
									fprintf(stderr, "El contenido de la variable \"%s\" no es un flotante.\n", varName.c_str());
									error = true;
									return 0.0;
								}
							}
						}
					}
				}
				else {
					fprintf(stderr, "No se encuentra la variable \"%s\" en la sección \"[%s]\" en el archivo .ini.\n", varName.c_str(), section.c_str());
					error = true;
					return 0.0;
				}
			}
		}
		temp = "";
	}
	fprintf(stderr, "No se encuentra la sección \"[%s]\" en el archivo .ini.\n", section.c_str());
	error = true;
	return 0.0;
}

/**
 * @brief Lee una cadena de caracteres guardada en una variable en el archivo .ini.
 * @param section Nombre de la sección donde está guardada la variable. No se debe poner entre corchetes.
 * @param varName Nombre de la variable a buscar en el archivo.
 * @return El valor de la variable o la cadena vacía si hubo un error.
 * @note Si devuelve la cadena vacía, utilizar errorStatus para decidir si fue un error o la variable tiene ese valor.
 */
string inifile_t::readString(string section, string varName){
	if(!input.is_open()){
		fprintf(stderr, "No se ha abierto un archivo '.ini', así que no se pueden leer valores.\n");
		error = true;
		return "";
	}

	int i;
	string temp = "";
	string temp2 = "[";
	temp2 += section;
	temp2 += "]";

	input.seekg(std::ios::beg);
	while(!input.eof()){
		getline(input, temp);
		if(temp2 == temp){
			temp2 = varName;
			while(!input.eof()){
				temp = "";
				getline(input, temp);
				if(temp[0] != '['){
					if(temp[0] != '#'){
						for(i = 0; temp[i] != '=' && temp[i] != '\0'; i++);
						if(temp[i] != '\0'){
							if(strncmp(temp.c_str(), temp2.c_str(), i) == 0){
								temp.erase(0, i+1);
								return temp;
							}
						}
					}
				}
				else {
					fprintf(stderr, "No se encuentra la variable \"%s\" en la sección \"[%s]\" en el archivo .ini.\n", varName.c_str(), section.c_str());
					error = true;
					return "";
				}
			}
		}
		temp = "";
	}
	fprintf(stderr, "No se encuentra la sección \"[%s]\" en el archivo .ini.\n", section.c_str());
	error = true;
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
	if(strcasecmp(temp.c_str(), "true") == 0){
		error = false;
		return true;
	}
	if(strcasecmp(temp.c_str(), "false") == 0){
		error = false;
		return false;
	}
	fprintf(stderr, "La variable \"%s\" de la sección \"[%s]\" del archivo .ini no contiene un valor booleano.\n", varName.c_str(), section.c_str());
	error = true;
	return false;
}

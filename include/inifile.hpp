#ifndef __INIFILE_T__
#define __INIFILE_T__

using std::string;
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
		inifile_t();
		inifile_t(string filename);
		~inifile_t();
		void open(string filename);
		int readInt(string section, string varName);
		double readDouble(string section, string varName);
		string readString(string section, string varName);
		bool readBool(string section, string varName);
		bool errorStatus(){ return error; }
};

/**
 * @fn inifile_t::errorStatus
 * @brief Devuelve el estado de la última operación realizada.
 * @return 1 en caso de error y 0 en otro caso.
 */

#endif

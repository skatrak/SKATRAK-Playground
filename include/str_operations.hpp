#ifndef __STR_OPERATIONS__
#define __STR_OPERATIONS__

const int ERROR_INT_VAL = 2147483647;

namespace str_op {
	int chartoint(char caracter);
	int strtoint(const char* cadena);
	double strtodouble(const char* cadena);
};

#endif

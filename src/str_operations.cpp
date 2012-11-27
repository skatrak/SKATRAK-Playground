#include "../include/str_operations.hpp"
#include <cstring>

/**
 * @brief Calcula el resultado de una potenciación.
 * @param base Base
 * @param exponent Exponente
 * @return Base^Exponente
 */
double exp(int base, int exponent){
	double temp = 1;
	if(exponent > 0){
		for(int i = 0; i < exponent; i++)
			temp *= base;
	}
	else {
		for(int i = exponent; i < 0; i++)
			temp /= base;
	}
	return temp;
}

/**
 * @brief Transforma un carácter ASCII del '0' al '9' a un entero con ese valor.
 * @param character Carácter ASCII que se va a transformar
 * @return -1 si no es un número o el número.
 */
int str_op::chartoint(char character){
	if(character <= '9' && character >= '0')
		return character - '0';
	return -1;
}

/**
 * @brief Convierte una cadena de caracteres de números a un número.
 * @param str Puntero a una cadena de caracteres acabada en un carácter nulo
 * @return ERROR_INT_VAL si la cadena no es de números y el número que representa en otro caso
 */
int str_op::strtoint(const char* str){
	int temp = 0, i = 0, length = strlen(str);
	bool negative = false;
	// Miramos si es un número negativo
	if(str[i] == '-'){
		negative = true;
		i++;
	}
	// Recorremos la cadena de caracteres
	while(str[i] != '\0'){
		// Si es un número se calcula su valor según su posición y si no lo es devolvemos un valor de error
		if(chartoint(str[i]) != -1){
			temp += (chartoint(str[i])*(int)exp(10, length-i-1));
			i++;
		}
		else return ERROR_INT_VAL;
	}
	// Si el número era negativo, hacemos un cambio de signo
	if(negative)
		return -temp;
	return temp;
}

/**
 * @brief Convierte una cadena de caracteres a un número flotante con precisión doble
 * @param str Puntero a una cadena de caracteres acabada en un carácter nulo
 * @return ERROR_INT_VAL si la cadena no representa a un número decimal o el número en otro caso
 */
double str_op::strtodouble(const char* str){
	double temp = 0.0;
	int i = 0, pointPos;
	bool negative = false;
	// Miramos si es un número negativo
	if(str[i] == '-'){
		negative = true;
		i++;
	}
	// Localizamos el punto decimal si lo hay. Si no lo hay se sitúa al final de la cadena
	while(str[i] != '.' && str[i] != '\0') i++;
	pointPos = i;
	// Iniciamos un bucle para calcular la parte entera del número decimal
	if(negative) i = 1;
	else i = 0;
	while(i < pointPos){
		if(chartoint(str[i]) != -1){
			temp += (chartoint(str[i])*exp(10, pointPos-i-1));
			i++;
		}
		else return (double)ERROR_INT_VAL;
	}
	// Calculamos la parte decimal
	if(str[pointPos] != '\0'){
		i = pointPos + 1;
		while(str[i] != '\0'){
			if(chartoint(str[i]) != -1){
				temp += (chartoint(str[i])*exp(10, -(i-pointPos)));
				i++;
			}
			else return (double)ERROR_INT_VAL;
		}
	}
	if(negative)
		return -temp;
	return temp;
}

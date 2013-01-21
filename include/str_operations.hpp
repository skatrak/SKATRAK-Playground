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

#ifndef __STR_OPERATIONS__
#define __STR_OPERATIONS__

const int ERROR_INT_VAL = 2147483647;						// Límite de rango positivo en C2 para 32 bits: (2^(32-1)) - 1
const double ERROR_DOUBLE_VAL = 1.7976931348623158e+308;	// +Infinito en precisión doble IEEE-754

namespace str_op {
	int chartoint(char caracter);
	int strtoint(const char* cadena);
	double strtodouble(const char* cadena);
};

#endif

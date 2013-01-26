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

#include <SKATRAK_PLAYGROUND.hpp>
#include <shared_attributes.hpp>
#include <conecta4/tablero.hpp>

bool salir(bool tablero_vacio){
	if(tablero_vacio) return true;

	messagebox_t msg(2);

	msg.setFont("AlteHaasGroteskRegular.ttf", 32);
	msg.setBackground("ventana_prueba.png");
	msg.setText(0, "¿Deseas abandonar la partida?");
	msg.setText(1, "Sí");
	msg.setText(2, "No");
	msg.locateTexts();

	switch(msg.loop(sistema->scr())){
	case 0: return true;
	case 1: return true;
	default: return false;
	}

}

void msgVictoria(ResultConecta4 ganador){
	string mensaje;
	messagebox_t msg(1);
	msg.setFont("AlteHaasGroteskRegular.ttf", 32);
	msg.setBackground("ventana_prueba.png");
	msg.setText(1, "Aceptar");

	switch(ganador){
	case P1_WINS:
		mensaje = "Ha ganado el jugador 1";
		break;
	case P2_WINS:
		mensaje = "Ha ganado el jugador 2";
		break;
	case NOBODY_WINS:
		mensaje = "Empate";
		break;
	default: break;
	}

	msg.setText(0, mensaje);
	msg.locateTexts();
	msg.loop(sistema->scr());
}

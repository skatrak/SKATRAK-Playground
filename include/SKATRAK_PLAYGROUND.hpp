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

#ifndef __SKATRAK_PLAYGROUND__
#define __SKATRAK_PLAYGROUND__

/* Incluimos las librerías estándar que necesitamos y las librerías SDL */
#include <string>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

using std::string;

/* Evitar Warnings en Microsoft Visual Studio */
#ifdef _MSC_VER
#define sprintf sprintf_s
#define strcasecmp strcmp
#endif

/* Incluimos las cabeceras generales compartidas por todos los minijuegos */
#include "./system.hpp"
#include "./music.hpp"
#include "./sfx.hpp"
#include "./image.hpp"
#include "./timekeeper.hpp"
#include "./font.hpp"
#include "./inifile.hpp"
#include "./messagebox.hpp"

/* Rutas por defecto de los recursos */
extern const char* MUS_PATH;
extern const char* SFX_PATH;
extern const char* FONT_PATH;
extern const char* IMG_PATH;
extern const char* INI_PATH;

/* El sistema tiene que poder utilizarse desde todos los módulos */
extern system_t* sistema;

#endif

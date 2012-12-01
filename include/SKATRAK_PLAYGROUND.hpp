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

/* Incluimos las cabeceras generales compartidas por todos los minijuegos */
#include "./system.hpp"
#include "./music.hpp"
#include "./sfx.hpp"
#include "./image.hpp"
#include "./timekeeper.hpp"
#include "./font.hpp"
#include "./inifile.hpp"

/* Rutas por defecto de los recursos */
extern const char* MUS_PATH;
extern const char* SFX_PATH;
extern const char* FONT_PATH;
extern const char* IMG_PATH;
extern const char* INI_PATH;

#endif

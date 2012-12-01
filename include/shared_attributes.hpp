#ifndef __SHARED_ATTRIBUTES__
#define __SHARED_ATTRIBUTES__

/* Valores de retorno de los menús */
enum returnVal	{	MAIN,			// Volver al menú principal
					ACTUAL_GAME,	// Volver al menú del juego actual
					EXIT,			// Salir del juego
					ERROR			// Salir con error
				};

extern system_t* sistema;
extern music_t* musica;

#endif

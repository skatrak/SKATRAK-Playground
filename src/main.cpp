#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../include/system.hpp"

system_t sistema(800, 600, 32);

int main(int argc, char* argv[]){
	sistema.toggleFullscreen();
	sistema.update();
	SDL_Delay(5000);
	sistema.toggleFullscreen();
	sistema.update();
	SDL_Delay(5000);
}

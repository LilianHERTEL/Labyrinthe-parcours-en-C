#include "xfenetre.h"

int main(int argc, char **argv) {	
	SDL_Windows *windows[4];
	int delay = 100;

	(void)argc;
	(void)argv;
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
	    exit(EXIT_FAILURE);
    }

	windows = createWindows();
	moveWindows(windows, delay);
	destroyWindows(windows);
	SDL_Quit();

	return 0;
}

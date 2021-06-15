#include "xfenetre.h"

int main(int argc, char **argv) {	
	SDL_Windows *windows[NB];
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

SDL_Window** createWindows(SDL_Windows *windows[], int delay) {
	int i = 0, cont = 1;
	
	while(i < NB && cont) {
		windows[i] = SDL_CreateWindow(i);
		if(windows[i] == NULL) {
			cont = 0;
		}
		++i;
	}
	if(cont == 0) {
		while(--i <= 0) {
			SDL_DestroyWindow(windows[i]);
			fputs("error windows", stderr);
		}
	}
}

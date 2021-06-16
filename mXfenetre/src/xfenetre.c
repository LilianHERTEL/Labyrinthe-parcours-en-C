#include "xfenetre.h"

int main(int argc, char **argv) {	
	SDL_Window *windows[NB];
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

/*
void moveWindows(SDL_Window *windows[], int delay) {
	int x0, y0, x1, y1, x2, y2, x3, y3, i;
	
	for(i = 0; i < NB; ++i) {
		
	}
	SDL_GetWindowPosition(windows[]
	SDL_SetWindowsP
}
*/
void createWindows(SDL_Window *windows[]) {
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

void destroyWindows(SDL_Window *windows[]) {
	int i;
	
	for(i = 0; i < NB; ++i) {
		SDL_DestroyWindow(windows[i]);
	}
}

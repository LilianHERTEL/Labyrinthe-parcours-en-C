#include "xfenetre.h"

int main(int argc, char **argv) {	
	SDL_Window *windows[NB];
	int delay = 200;

	(void)argc;
	(void)argv;
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
	    exit(EXIT_FAILURE);
    }

	createWindows(windows);
	moveWindows(windows, delay);
	destroyWindows(windows);
	SDL_Quit();

	return 0;
}
#include <stdio.h>
bool areInScreen(int x[], int y[], SDL_DisplayMode screen) {
	int i = 0;
	bool code = true;
	
	while(i < NB && code == true) {
		if(screen.w <= x[i] || x[i] < 0 || screen.h <= y[i] || y[i] < 0) {
			code = false;
			puts("fin de l'ecran");
		}
		++i;
	}
	return code;
}

void moveWindows(SDL_Window *windows[], int delay) {
	int x[NB], y[NB], i, width[NB], height[NB];
	SDL_DisplayMode screen;
	
	SDL_GetCurrentDisplayMode(0, &screen);
	for(i = 0; i < NB; ++i) {
		SDL_GetWindowSize(windows[i], &width[i], &height[i]);
		SDL_SetWindowPosition(windows[i], screen.w / 2, screen.h / 2);
		SDL_GetWindowPosition(windows[i], &x[i], &y[i]);
	}
	SDL_Delay(1500);
	i = 0;
	while(areInScreen(x, y, screen)) {
		SDL_SetWindowPosition(windows[0], x[0] + i, y[0] - i);
		SDL_GetWindowPosition(windows[0], &x[0], &y[0]);
		
		SDL_SetWindowPosition(windows[1], x[1] + i, y[1] + i);
		SDL_GetWindowPosition(windows[1], &x[1], &y[1]);
		
		SDL_SetWindowPosition(windows[2], x[2] - i, y[2] + i);
		SDL_GetWindowPosition(windows[2], &x[2], &y[2]);

		SDL_SetWindowPosition(windows[3], x[3] - i, y[3] - i);
		SDL_GetWindowPosition(windows[3], &x[3], &y[3]);
		
		SDL_Delay(delay);
		++i;
	}
	SDL_Delay(1000);
}

void createWindows(SDL_Window *windows[]) {
	int i = 0, cont = 1;
	
	while(i < NB && cont) {
		windows[i] = SDL_CreateWindow("fenetre", 0, 0, 300, 200, 0);
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

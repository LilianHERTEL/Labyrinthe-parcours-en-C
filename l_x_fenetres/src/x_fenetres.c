#include <stdio.h>
#include "mySDL.h"

int main(int argc, char const *argv[]) {
	int winWidth, 
		winHeight,
		i, 
		j = 0,
		nbWindows = 5,
		windowsShift;
	SDL_Window *window[nbWindows*4];
	SDL_Renderer *renderer = NULL;
	bool_t status;
	SDL_DisplayMode display;

	(void)argc;
	(void)argv;

	status = initializeSDL();
	if (!status) quitSDL(false, "Error : SDL initialization", NULL, NULL);

	SDL_GetCurrentDisplayMode(0, &display);
	winWidth = display.h/10;
	winHeight = winWidth;
	windowsShift = winHeight;
	
	// Création des fenêtres
	for (i = 0; i < nbWindows; i++) {
		window[i] = SDL_CreateWindow("Jeu de la vie", (display.w/2 - winWidth/2) + i*windowsShift - (nbWindows*winWidth)/2, (display.h/2 - winHeight/2) + i*windowsShift - (nbWindows*winWidth)/2, winWidth, winHeight, SDL_WINDOW_SHOWN);
		if (window[i] == NULL) {
			quitSDL(false, "Error : SDL window creation", window[i], NULL);
		}
	}
	SDL_Delay(1000);
    
    // Création du renderer
	/*
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
		quitSDL(false, "Error : SDL renderer creation", window, renderer);
    }*/
	
	//waitForQuitSDL();

	SDL_Delay(1000);

	for (i = 0; i < nbWindows*4; i++) {
		quitSDL(true, "SDL END", window[i], renderer);
	}

	return 0;
}

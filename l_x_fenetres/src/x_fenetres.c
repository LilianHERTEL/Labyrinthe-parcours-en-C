#include <stdio.h>
#include "mySDL.h"

void createWindows(SDL_Window* windows[], int nbWindows) {
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);
	int winWidth = display.h/10;
	int winHeight = winWidth;
	int windowsShift = winHeight;
	int i;
	for (i = 0; i < nbWindows; i++) {
		windows[i] = SDL_CreateWindow("Jeu de la vie", (display.w/2 - winWidth/2) + i*windowsShift - (nbWindows*winWidth)/2, (display.h/2 - winHeight/2) + i*windowsShift - (nbWindows*winWidth)/2, winWidth, winHeight, SDL_WINDOW_SHOWN);
		if (windows[i] == NULL) {
			quitSDL(false, "Error : SDL window creation", windows[i], NULL);
		}
	}
}

void moveWindows(SDL_Window* windows[], int nbWindows) {
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);
	int winWidth = display.h/10;
	int winHeight = winWidth;
	int windowsShift = winHeight;
	int i, winPosX, winPosY;
	for (i = 0; i < nbWindows; i++) {
		SDL_GetWindowPosition(windows[i], &winPosX, &winPosY);
		SDL_SetWindowPosition(windows[i], winPosX, (display.h/2 - winHeight/2) - i*windowsShift + (nbWindows*winWidth)/2 - winHeight);
	}
}

int main(int argc, char const *argv[]) {
	int nbWindows = 5, i;
	SDL_Window *windows[nbWindows*4];
	SDL_Renderer *renderer = NULL;
	bool_t status;

	(void)argc;
	(void)argv;

	status = initializeSDL();
	if (!status) quitSDL(false, "Error : SDL initialization", NULL, NULL);

	createWindows(windows, nbWindows);
	SDL_Delay(1000);
	moveWindows(windows, nbWindows);
	SDL_Delay(1000);

	for (i = 0; i < nbWindows*4; i++) {
		quitSDL(true, "SDL END", windows[i], renderer);
	}

	return 0;
}

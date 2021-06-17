#include <stdio.h>
#include "mySDL.h"
#include <SDL2/SDL_image.h>

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



SDL_Texture* loadTexture(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) quitSDL(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) quitSDL(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

void showTiles(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* background) {
	background = loadTexture("dirt_grass.png", window, renderer);

	SDL_Rect source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};    
	float zoom = 1;
	SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);               // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(background, NULL, NULL, &source.w, &source.h);  // Récupération des dimensions de l'image

	for (int i = 0; i < 10; i++) {
		destination.w = source.w * zoom;         // La destination est un zoom de la source
		destination.h = source.h * zoom;         // La destination est un zoom de la source
    	destination.x = (window_dimensions.w - destination.w) - i*source.w;     // La destination est au milieu de la largeur de la fenêtre
		destination.y = (window_dimensions.h - destination.h);  // La destination est au milieu de la hauteur de la fenêtre

		SDL_RenderCopy(renderer, background, &source, &destination);
	}
	for (int i = 0; i < 4; i++) {
		destination.w = source.w * zoom;         // La destination est un zoom de la source
     	destination.h = source.h * zoom;         // La destination est un zoom de la source
     	destination.x = (window_dimensions.w - destination.w) - i*source.w;     // La destination est au milieu de la largeur de la fenêtre
		 destination.y = (window_dimensions.h - destination.h) - source.h;  // La destination est au milieu de la hauteur de la fenêtre

		SDL_RenderCopy(renderer, background, &source, &destination);

		destination.w = source.w * zoom;         // La destination est un zoom de la source
		destination.h = source.h * zoom;         // La destination est un zoom de la source
		destination.x = (window_dimensions.w - destination.w) - i*source.w;     // La destination est au milieu de la largeur de la fenêtre
    	destination.y = (window_dimensions.h - destination.h) - 2*source.h;  // La destination est au milieu de la hauteur de la fenêtre
		SDL_RenderCopy(renderer, background, &source, &destination);
	}
}

int main(int argc, char const *argv[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture* background = NULL;
	
	bool_t status;

	(void)argc;
	(void)argv;

	status = initializeSDL();
	if (!status) quitSDL(false, "Error : SDL initialization", NULL, NULL);

	window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		quitSDL(false, "Error : SDL window creation", window, renderer);
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		quitSDL(false, "Error : SDL renderer creation", window, renderer);
		exit(EXIT_FAILURE);
	}
	
	showTiles(window, renderer, background);
	
	SDL_RenderPresent(renderer);  

	//createWindows(windows, nbWindows);
	SDL_Delay(1000);
	//moveWindows(windows, nbWindows);
	SDL_Delay(1000);

	SDL_DestroyTexture(background);
	IMG_Quit();
	quitSDL(true, "SDL END", window, renderer);

	return 0;
}

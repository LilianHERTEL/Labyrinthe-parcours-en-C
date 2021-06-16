#include <stdio.h>
#include <time.h>
#include "l_gameOfLife_view.h"
#include "l_gameOfLife.h"
#include "mySDL.h"

int main(int argc, char const *argv[]) {
    grid_t grid;
	int x = 100, y = 100, iterations = 100, sheight, swidth, delay = 100;
	rules_t *rules;
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool_t status;

	(void)argc;
	(void)argv;

	rules = malloc(sizeof(rules_t));
	if(rules == NULL) {
        printf("Error : memory allocation failed");
		return 1;
	}
	initLife(rules);	
	
	srand(time(0));
	
	status = initializeSDL();
	if (!status) quitSDL(false, "Error : SDL initialization", NULL, NULL);
	
    
    if(screenSize(&sheight, &swidth) != 0) {
		free(rules);
		quitSDL(false, "Error : SDL display mode", NULL, NULL);
    }
	
	// Création de la fenetre
    window = SDL_CreateWindow("Jeu de la vie", 0, sheight/2 - sheight/4, swidth/2, sheight/2, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
		free(rules);
		quitSDL(false, "Error : SDL window creation", window, NULL);
    }
    
    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        free(rules);
		quitSDL(false, "Error : SDL renderer creation", window, renderer);
    }
	
	grid = createGrid(x, y);
	if(grid.grid == NULL) {
		free(rules);
		quitSDL(false, "Error : Grid creation", window, renderer);
	}
	
	initializeRandomGrid(grid);
	displayGrid(grid);
	drawGrid(renderer, grid);

	startGoL(grid, rules, iterations, delay, renderer);

	SDL_Delay(delay);
	initMaze(rules);
	startGoL(grid, rules, iterations, delay, renderer);

	waitForQuitSDL();
	
	free(rules);
	freeGrid(grid);
	quitSDL(true, "SDL END", window, renderer);

	return 0;
}

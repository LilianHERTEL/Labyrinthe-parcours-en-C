#include <stdio.h>
#include "l_gameOfLife_view.h"
#include "l_gameOfLife.h"
#include <time.h>

int main(int argc, char const *argv[]) {
    grid_t grid;
	int x = 100, y = 100, i, iterations = 100, sheight, swidth, delay = 100;
	rules_t *rules;
	SDL_Window *window;
	SDL_Renderer *renderer;

	(void)argc;
	(void)argv;

	rules = malloc(sizeof(rules_t));
	if(rules == NULL) {
        printf("Error : memory allocation failed");
		return 1;
	}
	initLife(rules);	
	
	srand(time(0));
	
	/* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        free(rules);
        exit(EXIT_FAILURE);
    }
    
    if(screenSize(&sheight, &swidth) != 0)
    {
        SDL_Log("Error : SDL Display Mode - %s\n", SDL_GetError()); 
        SDL_Quit();
        free(rules);
        exit(EXIT_FAILURE);
    }
	
	//creation de la fenetre
    window = SDL_CreateWindow("Jeu de la vie", 0, sheight/2 - sheight/4, swidth/2, sheight/2, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        free(rules);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    //creation du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Error : SDL renderer creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        free(rules);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
	
	grid = createGrid(x, y);
	if(grid.grid == NULL) {
		fputs("error in grid creation", stderr);
		free(rules);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
	}
	
	initializeRandomGrid(grid);
	displayGrid(grid);
	drawGrid(renderer, grid);

	for(i = 0; i < iterations; ++i) {
		nextIteration(&grid, rules);
		drawGrid(renderer, grid);
		displayGrid(grid);
		SDL_Delay(delay);
	}

	SDL_Delay(delay);
	initMaze(rules);
	
	for(i = 0; i < iterations; ++i) {
		nextIteration(&grid, rules);
		drawGrid(renderer, grid);
		displayGrid(grid);
		SDL_Delay(delay);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	free(rules);
	freeGrid(grid);
	SDL_Quit();

	return 0;
}

#include "gameoflife.h"

int main() {
	Grid_t grid;
	int x = 10, y = 10, i, iterations = 5, sheight, swidth, delay = 3000;
	Rule_t *life;
	SDL_Window *window;
	SDL_Renderer *renderer;

	life = malloc(sizeof(Rule_t));
	
	if(life == NULL) {
		return GOLERRORCODE;
	}
	
	initLife(life);	
	
	//initialisation de l'aleatoire
	srand(time(0));
	
	/* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        free(life);
        exit(EXIT_FAILURE);
    }
    
    
    if(tailleEcran(&sheight, &swidth) != 0)
    {
        SDL_Log("Error : SDL Display Mode - %s\n", SDL_GetError()); 
        SDL_Quit();
        free(life);
        exit(EXIT_FAILURE);
    }
	
	//creation de la fenetre
    window = SDL_CreateWindow("Jeu de la vie", 0, sheight/2 - sheight/4, swidth/2, sheight/2, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        free(life);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    //creation du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Error : SDL renderer creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        free(life);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
	
	grid = createGrid(x, y);
	if(grid.grid == NULL) {
		fputs("error in grid creation", stderr);
		return GOLERRORCODE;
	}
	
	initializeRandomGrid(grid);
	displayGrid(grid);
	drawGrid(renderer, grid);
	/*
	for(i = 0; i < iterations; ++i) {
		nextIteration(&grid, life);
		drawGrid(renderer, grid);
		displayGrid(grid);
		SDL_Delay(delay);
	}
	*/
	SDL_Delay(delay);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	free(life);
	freeGrid(grid);
	SDL_Quit();
	return 0;
}

void drawGrid(SDL_Renderer *renderer, Grid_t grid) {
	int i, j, width, height;
	SDL_Rect rectangle;
	
	SDL_GetRendererOutputSize(renderer, &width, &height);
	//SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	//rectangle.w = height / grid.x;
	rectangle.w = 10;
	//rectangle.h = height / grid.y;
	rectangle.h = 10;
	for(i = 0; i < grid.x; ++i) {
		rectangle.x = rectangle.w * i;
		for(j = 0; j < grid.y; ++j) {
			rectangle.y = rectangle.h * i;
			if(!grid.grid[i][j]) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			SDL_RenderFillRect(renderer, &rectangle);
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderPresent(renderer);
		}
	}
}

int tailleEcran(int *h, int* w)
{
    SDL_DisplayMode current;
    int code = 0;

    if(SDL_GetCurrentDisplayMode(0, &current) != 0)
   {
       code = 1;
   }
   else
   {
        *h = current.h;
        *w = current.w;
   }
    return code;
}

void freeGrid(Grid_t grid) {
	int i;
	
	for(i = grid.x - 1; i >= 0 ; --i) {
		free(grid.grid[i]);
	}
	free(grid.grid);
}

Grid_t createGrid(int x, int y) {
	int i;
	Grid_t grid;

	grid.x = x;
	grid.y = y;
	
	grid.grid = malloc(sizeof(bool *) * x);
	if(grid.grid != NULL) {
		for(i = 0; i < x; ++i) {
			grid.grid[i] = (bool *)malloc(sizeof(bool) * y);
			if(grid.grid[i] == NULL) {
				fprintf(stderr, "error initializing line %d\n", i);
			}
		}
	}
	else {
		fputs("error initializing rows\n", stderr);
	}
	return grid;
}

bool initializeSDL(void) {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    	return 0; 
	}
	return 1;
}


void initializeBlankGrid(Grid_t grid) {
	int i, j;
	
	for(i = 0; i < grid.x; ++i) {
		for(j = 0; j < grid.y; ++j) {
			grid.grid[i][j] = 0;
		}
	}
}

//implementation provisoire
void displayGrid(Grid_t grid) {
	int i, j;
	
	for(i = 0; i < grid.x; ++i) {
		for(j = 0; j < grid.y; ++j) {
			printf("%d ", grid.grid[i][j]);
		}
		puts("");
	}
	puts("");
}


void initializeRandomGrid(Grid_t grid) {
	int i, j;
	
	for(i = 0; i < grid.x; ++i) {
		for(j = 0; j < grid.y; ++j) {
			grid.grid[i][j] = rand()%2;
		}
	}
}

void nextIteration(Grid_t *grid, Rule_t *rule) {
	Grid_t result;
	int i, j, k, l, m, n, neighbours;
	
	result = createGrid(grid->x, grid->y);
	
	for(i = 0; i < grid->x; ++i) {
		for(j = 0; j < grid->y; ++j) {
			neighbours = 0;
			for(k = -1; k < 2; ++k) {
				for(l = -1; l < 2; ++l) {
					m = (i+k) % grid->x;
					n = (j+l) % grid->y;
					if(m < 0) {
						m = grid->x - 1;
					}
					if(n < 0) {
						n = grid->y - 1;
					}
					neighbours = neighbours + (int)grid->grid[m][n];
				}
			}
			neighbours -= grid->grid[i][j];
			if(grid->grid[i][j]) {
				result.grid[i][j] = rule->survie[neighbours];
			}
			else {
				result.grid[i][j] = rule->naissance[neighbours];
			}
		}
	}
	freeGrid(*grid);
	*grid = result;
}

void initLife(Rule_t *life) {
	int i;
	
	for(i = 0; i < 9; ++i) {
		switch(i) {
			case 3:
				life->naissance[i] = 1;
			case 2:
				life->survie[i] = 1;
				break;
			default:
				life->naissance[i] = 0;
				life->survie[i] = 0;
		}
	}
}


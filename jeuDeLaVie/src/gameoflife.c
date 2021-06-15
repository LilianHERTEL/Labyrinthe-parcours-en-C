#include "gameoflife.h"

void freeGrid(Grid_t grid) {
	int i;
	
	for(i = grid.x - 1; i >= 0 ; --i) {
		free(grid.grid[i]);
	}
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

void quitSDL(void) {
	SDL_Quit();
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

int main() {
	Grid_t grid;
	int x = 10, y = 10, i, iterations = 30;
	Rule_t *life;
	
	life = malloc(sizeof(Rule_t));
	
	if(life == NULL) {
		return GOLERRORCODE;
	}
	
	initLife(life);
	
	//initialisation de l'aleatoire
	srand(time(0));
	
	if(!initializeSDL()) {
		return GOLERRORCODE;
	}
	
	grid = createGrid(x, y);
	if(grid.grid == NULL) {
		fputs("error in grid creation", stderr);
		return GOLERRORCODE;
	}
	
	initializeBlankGrid(grid);
	displayGrid(grid);
	
	initializeRandomGrid(grid);
	displayGrid(grid);
	
	for(i = 0; i < iterations; ++i) {
		nextIteration(&grid, life);
		displayGrid(grid);
	}
	
	free(life);
	freeGrid(grid);
	quitSDL();
	return 0;
}

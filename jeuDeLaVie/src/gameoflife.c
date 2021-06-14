#include "gameoflife.h"

void freeGrid(Grid_t grid, int x) {
	int i;
	
	for(i = x-1; i >= 0 ; --i) {
		free(grid[i]);
	}
	free(grid);
}

Grid_t createGrid(int x, int y) {
	Grid_t grid;
	int i;
	
	grid = malloc(sizeof(booleen*) * x);
	
	if(grid == NULL) {
		fputs("error initializing grid\n", stderr);
	}
	else {
		for(i = 0; i < x; ++i) {
			grid[i] = malloc(sizeof(booleen) * y);
			if(grid[i] == NULL) {
				fprintf(stderr, "error initializing line %d\n", i);
			}
		}
	}
	return grid;
}


booleen initializeSDL(void) {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    	return 0; 
	}
	return 1;
}


void initializeBlankGrid(Grid_t grid, int x, int y) {
	int i;
	
	for(i = 0; i < x; ++i) {
		memset(grid[i], 0, y);
	}
}

//implementation provisoire
void displayGrid(Grid_t grid, int x, int y) {
	int i, j;
	
	for(i = 0; i < x; ++i) {
		for(j = 0; j < y; ++j) {
			printf("%d ", grid[i][j]);
		}
		puts("");
	}
	puts("");
}


void initializeRandomGrid(Grid_t grid, int x, int y) {
	int i, j;
	
	for(i = 0; i < x; ++i) {
		for(j = 0; j < y; ++j) {
			grid[i][j] = rand()%2;
		}
	}
}

void nextIteration(Grid_t grid, int x, int y, Rule_t *rule) {
	Grid_t result;
	int i, j, k, l, m, n, neighbours;
	
	result = createGrid(x, y);
	
	for(i = 0; i < x; ++i) {
		for(j = 0; j < y; ++j) {
			neighbours = 0;
			for(k = -1; k < 2; ++k) {
				for(l = -1; l < 2; ++l) {
					m = i+k % x;
					n = j+l % y;
					if(m < 0) {
						m = x-1;
					}
					if(n < 0) {
						n = y-1;
					}
					neighbours = neighbours + (int)grid[m][n];
				}
			}
			neighbours -= grid[i][j];
			if(grid[i][j]) {
				result[i][j] = rule->survie[neighbours];
			}
			else {
				result[i][j] = rule->naissance[neighbours];
			}
		}
	}
	freeGrid(grid, x);
	grid = result;
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

int main(int argc, char **argv) {
	Grid_t grid;
	int x = 10, y = 10, i, iterations = 3;
	Rule_t *life;
	
	life = malloc(sizeof(Rule_t));
	initLife(life);
	
	if(life == NULL) {
		return GOLERRORCODE;
	}
	
	//initialisation de l'aleatoire
	srand(time(0));
	
	if(!initializeSDL()) {
		return GOLERRORCODE;
	}
	
	grid = createGrid(x, y);
	if(grid == NULL) {
		fputs("error in grid creation", stderr);
		return GOLERRORCODE;
	}
	
	initializeBlankGrid(grid, x, y);
	if(grid == NULL) {
		fputs("error in grid blank initialization", stderr);
		return GOLERRORCODE;
	}
	displayGrid(grid, x, y);
	
	initializeRandomGrid(grid, x, y);
	if(grid == NULL) {
		fputs("error in grid blank initialization", stderr);
		return GOLERRORCODE;
	}
	displayGrid(grid, x, y);
	
	for(i = 0; i < iterations; ++i) {
		nextIteration(grid, x, y, life);
		displayGrid(grid, x, y);
	}
	
	free(life);
	freeGrid(grid, x);
	quitSDL();
	return 0;
}

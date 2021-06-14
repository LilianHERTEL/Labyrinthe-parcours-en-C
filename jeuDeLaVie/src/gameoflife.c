#include "gameoflife.h"

void freeGrid(Grid_t grid, int x) {
	int i;
	
	for(i = 0; i < x; ++i) {
		free(grid[i]);
	}
	free(grid);
}

Grid_t createGrid(int x, int y) {
	Grid_t grid;
	int i;
	
	grid = malloc(sizeof(bool*) * x);
	
	if(grid == NULL) {
		fputs("error initializing grid\n", stderr);
	}
	else {
		for(i = 0; i < x; ++i) {
			grid[i] = malloc(sizeof(bool) * y);
			if(grid[i] == NULL) {
				fprintf(stderr, "error initializing line %d\n", i);
			}
		}
	}
	return grid;
}

/*
void initializeSDL(void);
void initializeBlankGrid(Grid_t grid);
void initializeRandomGrid(Grid_t grid);
void displayGrid(Grid_t grid);
void nextIteration(Grid_t grid);
*/

int main(int argc, char **argv) {
	Grid_t grid;
	int x = 10, y = 10, i, iterations = 30;
	
//	initializeSDL();
	grid = createGrid(x, y);
	if(grid == NULL) {
		fputs("error in grid creation", stderr);
		return GOLERRORCODE;
	}
/*	initializeBlankGrid(grid);
	if(grid == NULL) {
		fputs("error in grid blank initialization", stderr);
		return GOLERRORCODE;
	}
	displayGrid(grid);
	initializeRandomGrid(grid);
	if(grid == NULL) {
		fputs("error in grid blank initialization", stderr);
		return GOLERRORCODE;
	}
	for(i = 0; i < iterations; ++i) {
		nextIteration(grid);
		displayGrid(grid);
	}
*/
	freeGrid(grid, x);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "bool.h"

grid_t createGrid(int x, int y) {
	int i;
	grid_t grid;

	grid.x = x;
	grid.y = y;
	
	grid.grid = malloc(sizeof(bool_t*) * x);
	if(grid.grid != NULL) {
		for(i = 0; i < x; ++i) {
			grid.grid[i] = (bool_t*)malloc(sizeof(bool_t) * y);
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

void initializeBlankGrid(grid_t grid) {
	int i, j;
	
	for(i = 0; i < grid.x; ++i) {
		for(j = 0; j < grid.y; ++j) {
			grid.grid[i][j] = 0;
		}
	}
}

void initializeRandomGrid(grid_t grid) {
	int i, j;
	
	for(i = 0; i < grid.x; ++i) {
		for(j = 0; j < grid.y; ++j) {
			grid.grid[i][j] = rand()%2;
		}
	}
}

void displayGrid(grid_t grid) {
	int i, j;
	
	for(i = 0; i < grid.x; ++i) {
		for(j = 0; j < grid.y; ++j) {
			printf("%d ", grid.grid[i][j]);
		}
		puts("");
	}
	puts("");
}

void freeGrid(grid_t grid) {
	int i;
	
	for(i = grid.x - 1; i >= 0 ; --i) {
		free(grid.grid[i]);
	}
	free(grid.grid);
}
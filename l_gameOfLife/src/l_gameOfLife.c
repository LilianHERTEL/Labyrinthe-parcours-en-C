#include <SDL2/SDL.h>
#include <stdio.h>
#include "l_gameOfLife.h"
#include "bool.h"

void initLife(rules_t *life) {
	int i;
	
	for(i = 0; i < 9; ++i) {
		switch(i) {
			case 3:
				life->naissance[i] = 1;
				life->survie[i] = 1;
				break;
			case 2:
				life->survie[i] = 1;
				break;
			default:
				life->naissance[i] = 0;
				life->survie[i] = 0;
		}
	}
}

void initMaze(rules_t *maze) {
  int i;
	
	for(i = 0; i < 9; ++i) {
		switch(i) {
			case 0:
				maze->survie[i] = 0;
				maze->naissance[i] = 0;
				break;
			case 5:
				maze->survie[i] = 0;
				maze->naissance[i] = 0;
				break;
			case 3:
				maze->naissance[i] = 1;
				maze->survie[i] = 1;
				break;
			default:
				maze->survie[i] = 1;
				maze->naissance[i] = 0;
		}
	}
}

void nextIteration(grid_t *grid, rules_t *rule) {
	grid_t result;
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
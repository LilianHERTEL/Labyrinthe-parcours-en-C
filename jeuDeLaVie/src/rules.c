#include "rules.h"

void initLife(rule_t *life) {
	int i;
	
	for(i = 0; i < TAILLE; ++i) {
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

void initMaze(rule_t *maze) {
	int i;
	
	for(i = 0; i < TAILLE; ++i) {
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

void nextIteration(int ** grid, int n, int m, rule_t *rule) {
	int ** result;
	int i, j, k, l, ma, na, neighbours;
	
	result = createGrid(n, m);
	
	for(i = 0; i < n; ++i) {
		for(j = 0; j < m; ++j) {
			neighbours = 0;
			for(k = -1; k < 2; ++k) {
				for(l = -1; l < 2; ++l) {
					ma = (i+k) % na;
					na = (j+l) % ma;
					if(ma < 0) {
						ma = na - 1;
					}
					if(na < 0) {
						na = ma - 1;
					}
					neighbours = neighbours + grid[ma][na];
				}
			}
			neighbours -= grid[i][j];
			if(grid[i][j]) {
				result[i][j] = rule->survie[neighbours];
			}
			else {
				grid[i][j] = rule->naissance[neighbours];
			}
		}
	}
	freeGrid(grid);
	grid = result;
}

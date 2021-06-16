#include "rules.h"

void initLife(rule_t *life) {
	int i;
	
	for(i = 0; i < TAILLE; ++i) {
		switch(i) {
			case 3:
				life->naissance[i] = true;
				life->survie[i] = true;
				break;
			case 2:
				life->naissance[i] = false;
				life->survie[i] = true;
				break;
			default:
				life->naissance[i] = false;
				life->survie[i] = false;
		}
	}
}

void initMaze(rule_t *maze) {
	int i;
	
	for(i = 0; i < TAILLE; ++i) {
		switch(i) {
			case 0:
				maze->survie[i] = false;
				maze->naissance[i] = false;
				break;
			case 5:
				maze->survie[i] = false;
				maze->naissance[i] = false;
				break;
			case 3:
				maze->naissance[i] = true;
				maze->survie[i] = true;
				break;
			default:
				maze->survie[i] = true;
				maze->naissance[i] = false;
		}
	}
}

void nextIteration(int *** grid, int n, int m, rule_t *rule) {
	int ** result;
	int i, j, k, l, ma, na, neighbours;
	
	result = allocGrid(n, m);
	
	for(i = 0; i < n; ++i) {
		for(j = 0; j < m; ++j) {
			neighbours = 0;
			for(k = -1; k < 2; ++k) {
				for(l = -1; l < 2; ++l) {
					ma = (i+k) % n;
					na = (j+l) % m;
					if(ma < 0) {
						ma = n - 1;
					}
					if(na < 0) {
						na = m - 1;
					}
					neighbours = neighbours + (*grid)[ma][na];
				}
			}
			neighbours -= (*grid)[i][j];
			if((*grid)[i][j] == 1) {
				result[i][j] = (int)(!rule->survie[neighbours]);
			}
			else {
				result[i][j] = (int)(!rule->naissance[neighbours]);
			}
		}
	}
	freeGrid(*grid, n);
	*grid = result;
}

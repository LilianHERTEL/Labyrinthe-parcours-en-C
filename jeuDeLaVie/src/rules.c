#include "rules.h"

void initLife(rule_t *life) {
	int i;
	
	for(i = 0; i < TAILLE; ++i) {
		life->naissance[i] = false;
		life->survie[i] = false;
	}
	life->naissance[3] = true;
	life->survie[2] = true;
	life->survie[3] = true;
}

void initMaze(rule_t *maze) 
{
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


int getNeighbours(int ** grid, int n, int m, int i, int j)
{
	int neighbours = 0;

	if(i - 1 >= 0)
	{
		if(grid[i-1][j] == 1)
			neighbours++;
	}
	else
	{
		if(grid[n-1][j] == 1) 
		{
			neighbours++;
		}
	}
	if(i + 1 < n )
	{
		if(grid[i+1][j] == 1)
			neighbours++;
	}
	else
	{
		if(grid[0][j] == 1) 
		{
			neighbours++;
		}
	}

	if(j - 1 >= 0 )
	{
		if(grid[i][j-1] == 1)
			neighbours++;
	}
	else
	{
		if(grid[i][m-1] == 1) 
		{
			neighbours++;
		}
	}
	if(j + 1 < m)
	{
		if(grid[i][j+1] == 1)
			neighbours++;
	}
	else
	{
		if(grid[i][0] == 1) 
		{
			neighbours++;
		}
	}
	return neighbours;
}

void nextIteration(int *** grid, int n, int m, rule_t *rule) {
	int ** result;
	int    i, 
	       j, 
		   neighbours;
	
	result = allocGrid(n, m);
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++) {
			neighbours = getNeighbours(*grid, n, m, i, j);
			
			if((*grid)[i][j] == 1) 
			{
				result[i][j] = rule->survie[neighbours];
			}
			else 
			{
				result[i][j] = rule->naissance[neighbours];
			}
		}
	}
	freeGrid(*grid, n);
	*grid = result;
}

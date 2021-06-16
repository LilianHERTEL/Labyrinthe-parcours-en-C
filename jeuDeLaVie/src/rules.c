#include "rules.h"

/**
 * @brief Initialise les regles de vie
 * 
 * @param life regles
 */
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

/**
 * @brief Initialise les regles de labyrinthe
 * 
 * @param maze regles
 */
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

/**
 * @brief Donne le nombre de voisins d'une cellule
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 * @param i indice ligne de la cellule
 * @param j indice colonne de la cellule
 * @return int 
 */
int getNeighbours(int ** grid, int n, int m, int i, int j)
{
	int neighbours = 0;

	if(grid[(i-1 + n) % n][j] == 1)
	{
		neighbours++;
	}
	if(grid[(i+1 + n) % n][j] == 1)
	{
		neighbours++;
	}
	if(grid[i][(j-1 + m)%m] == 1)
	{
		neighbours++;
	}
	if(grid[i][(j+1 + m)%m] == 1)
	{
		neighbours++;
	}
	return neighbours;
}

/**
 * @brief Fait evoluer la matrice selon les regles
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 * @param rule regles
 */
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

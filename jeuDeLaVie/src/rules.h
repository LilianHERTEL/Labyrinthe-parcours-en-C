#include <stdio.h>
#include "matrice.h"
#include "booleen.h"

#define TAILLE 9

typedef struct {
	booleen_t survie[TAILLE];
	booleen_t naissance[TAILLE];
} rule_t;

void initLife(rule_t *life);
void initMaze(rule_t *maze); 
void nextIteration(int *** grid, int n, int m, rule_t *rule);
int getNeighbours(int ** grid, int n, int m, int i, int j);
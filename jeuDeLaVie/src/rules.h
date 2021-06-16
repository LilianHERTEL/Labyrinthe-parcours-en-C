#include <stdio.h>
#include "matrice.h"

#define TAILLE 9

typedef struct {
	int survie[TAILLE];
	int naissance[TAILLE];
} rule_t;

void initLife(rule_t *life);
void nextIteration(int *** grid, int n, int m, rule_t *rule);
int getNeighbours(int ** grid, int n, int m, int i, int j);
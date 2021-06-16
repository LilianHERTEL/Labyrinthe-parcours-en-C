#include <stdio.h>
#include "booleen.h"
#include "matrice.h"

#define TAILLE 9

typedef struct {
	booleen_t survie[TAILLE];
	booleen_t naissance[TAILLE];
} rule_t;

void initLife(rule_t *life);
void nextIteration(int *** grid, int n, int m, rule_t *rule);
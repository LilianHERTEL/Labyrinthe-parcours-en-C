#pragma once
#include "bool.h"
#include "grid.h"

typedef struct {
	bool_t survie[9];
	bool_t naissance[9];
} rules_t;


void initLife(rules_t *life);
void initMaze(rules_t *maze);
void nextIteration(grid_t *grid, rules_t *rules);
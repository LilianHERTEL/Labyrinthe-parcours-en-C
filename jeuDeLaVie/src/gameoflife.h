#pragma once

#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <time.h>

#define GOLERRORCODE 1

#include <SDL2/SDL.h>

typedef enum { True, False } booleen;

typedef booleen** Grid_t;
typedef struct {
	booleen survie[9];
	booleen naissance[9];
} Rule_t;

void initLife(Rule_t *life);
Grid_t createGrid(int x, int y);
booleen initializeSDL(void);
void quitSDL(void);
void initializeBlankGrid(Grid_t grid, int x, int y);
void initializeRandomGrid(Grid_t grid, int x, int y);
void displayGrid(Grid_t grid, int x, int y);
void nextIteration(Grid_t grid, int x, int y, Rule_t *rule);
void freeGrid(Grid_t grid, int x);

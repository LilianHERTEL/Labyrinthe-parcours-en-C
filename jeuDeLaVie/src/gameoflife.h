#pragma once

#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <time.h>

#define GOLERRORCODE 1

#include <SDL2/SDL.h>

typedef enum { true, false } bool;

typedef struct {
	bool **grid;
	int x;
	int y;
} Grid_t;

typedef struct {
	bool survie[9];
	bool naissance[9];
} Rule_t;

void initLife(Rule_t *life);
Grid_t createGrid(int x, int y);
bool initializeSDL(void);
void quitSDL(void);
void initializeBlankGrid(Grid_t grid);
void initializeRandomGrid(Grid_t grid);
void displayGrid(Grid_t grid);
void nextIteration(Grid_t *grid, Rule_t *rule);
void freeGrid(Grid_t grid);
int tailleEcran(int *height, int *width);

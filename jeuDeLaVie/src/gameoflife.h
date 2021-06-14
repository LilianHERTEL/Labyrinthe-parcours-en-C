#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define GOLERRORCODE 1

#include <SDL2/SDL.h>

typedef bool** Grid_t;

Grid_t createGrid(int x, int y);
bool initializeSDL(void);
void quitSDL(void);
void initializeBlankGrid(Grid_t grid);
void initializeRandomGrid(Grid_t grid);
void displayGrid(Grid_t grid);
void nextIteration(Grid_t grid);
void freeGrid(Grid_t grid, int x);

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define GOLERRORCODE 1

#include <SDL2/sdl.h>

typedef bool** Grid_t;

Grid_t createGrid(int x, int y);
void initializeSDL(void);
void initializeBlankGrid(Grid_t grid);
void initializeRandomGrid(Grid_t grid);
void displayGrid(Grid_t grid);
void nextIteration(Grid_t grid);

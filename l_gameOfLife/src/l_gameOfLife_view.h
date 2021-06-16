#pragma once 
#include <SDL2/SDL.h>
#include "grid.h"
#include "l_gameOfLife.h"

void drawGrid(SDL_Renderer *renderer, grid_t grid);
int screenSize(int *height, int *width);
void startGoL(grid_t grid, rules_t* rules, int iterations, int delay, SDL_Renderer* renderer);
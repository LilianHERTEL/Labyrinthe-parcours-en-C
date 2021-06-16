#pragma once 
#include <SDL2/SDL.h>
#include "grid.h"

void drawGrid(SDL_Renderer *renderer, grid_t grid);
int screenSize(int *height, int *width);
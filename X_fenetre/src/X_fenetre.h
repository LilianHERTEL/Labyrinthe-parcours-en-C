#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int taileEcran(int *h, int* w);

void deplacerFenetres(SDL_Window  * window_1,SDL_Window * window_2,SDL_Window* window_4, SDL_Window* window_5, int pas);
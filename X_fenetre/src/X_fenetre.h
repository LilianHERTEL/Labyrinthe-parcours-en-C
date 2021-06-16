#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define NB_FENETRES 6

int taileEcran(int *h, int* w);

void deplacerFenetre(SDL_Window  * window, int pas);
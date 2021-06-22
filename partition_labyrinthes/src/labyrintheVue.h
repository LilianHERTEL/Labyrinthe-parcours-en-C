#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "mySDL.h"

typedef enum
{
    NORD = 1,
    SUD = 2,
    EST = 4,
    OUEST = 8
}directions;

void drawLab(SDL_Window * window, SDL_Renderer * renderer, int ** grille, int n, int m);
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mySDL.h"

typedef enum
{
    NORD = 1,
    SUD = 2,
    EST = 4,
    OUEST = 8
}directions;

void drawLab(SDL_Window * window, SDL_Renderer * renderer, int ** grille, int n, int m, SDL_Texture * wallTexture, SDL_Texture * groundTexture);

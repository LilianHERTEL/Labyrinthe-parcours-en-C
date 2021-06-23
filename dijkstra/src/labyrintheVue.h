#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mySDL.h"
#include "grapheListeAretes.h"
#include "kruskal_non_arbo.h"
#include "dijkstra.h"
#include "liste_chainee.h"

typedef enum
{
    NORD = 1,
    SUD = 2,
    EST = 4,
    OUEST = 8
}directions;

void dimensionTile(SDL_Rect *tile, SDL_Rect positionLab, int n, int m);

void dimensionPerso(SDL_Rect * perso, SDL_Rect tile);

void drawperso(SDL_Renderer *renderer, SDL_Texture *perso, SDL_Rect dest);

void drawLab(SDL_Renderer *renderer, int **grid, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture);

void drawOtherTile(SDL_Renderer *renderer, int indiceNoeud, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture);

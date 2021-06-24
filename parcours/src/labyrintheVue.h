#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "mySDL.h"

typedef enum
{
    NORD = 1,
    SUD = 2,
    EST = 4,
    OUEST = 8
} directions;

void dimensionsLab(SDL_Rect *positionLab, SDL_Rect tile, int n, int m);

void dimensionTile(SDL_Rect *tile, SDL_Rect positionLab, int n, int m);

void dimensionPerso(SDL_Rect *perso, SDL_Rect tile);

void drawperso(SDL_Renderer *renderer, SDL_Texture *perso, SDL_Rect dest);

void drawLab(SDL_Renderer *renderer, int **grid, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, bool_t *marques);

void drawStone(SDL_Renderer *renderer, int indiceNoeud, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture);

void drawAll(bool_t *marques, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso);

bool_t drawText(char *text, SDL_Rect dest, TTF_Font *font, SDL_Renderer *renderer);

void dimensionButtons(SDL_Rect *dijkstra, SDL_Rect *a_etoile, SDL_Rect *profondeur, SDL_Rect *quit, SDL_Rect positionLab);

void drawMenu(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect positionLab, SDL_Rect dijkstra, SDL_Rect a_etoile, SDL_Rect profondeur, SDL_Rect quit);

void menuLoop(SDL_Renderer * renderer, TTF_Font *font, SDL_Texture *texture, SDL_Texture *perso);
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mySDL.h"

// Type direction (pour savoir quels murs placer)
typedef enum
{
    NORD = 1,
    SUD = 2,
    EST = 4,
    OUEST = 8
} directions;

/**
 * @brief Dessine le labyrinthe a l'ecran
 * 
 * @param window La fenetre
 * @param renderer Le rendu de la fenetre
 * @param grid La grille representant le labyrinthe
 * @param n Le nombre de lignes de la grille
 * @param m Le nombre de colonnes de la grille
 * @param texture La texture chargée, pour les murs et le sol
 */
void drawLab(SDL_Window *window, SDL_Renderer *renderer, int **grid, int n, int m, SDL_Texture *texture);

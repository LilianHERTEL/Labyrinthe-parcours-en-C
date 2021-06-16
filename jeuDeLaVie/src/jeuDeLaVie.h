#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "matrice.h"
#include "rules.h"

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer); 

/**
 * @brief Affiche une matrice d'entiers dans la fenetre
 * 
 * @param window 
 * @param renderer 
 * @param grille 
 * @param n 
 * @param m 
 */
void drawGrid(SDL_Window * window, SDL_Renderer *renderer, int ** grille, int n, int m); 
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "matrice.h"
#include "rules.h"

/**
 * @brief Termine en quittant la sdl
 * 
 * @param ok 
 * @param msg 
 * @param window 
 * @param renderer 
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
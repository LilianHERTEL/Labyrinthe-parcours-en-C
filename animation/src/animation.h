#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);

void placerImage(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer, float zoom, float destX, float destY);

void animation(SDL_Texture *sol,SDL_Texture * fond, SDL_Texture * perso, SDL_Window * window, SDL_Renderer * renderer);
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

/**
 * @brief Place une image a un endroit indique dans le render
 * 
 * @param my_texture la texture (image) a placer
 * @param window la fenetre
 * @param renderer le rendu de la fenetre
 * @param zoom le niveau de zoom a appliquer
 * @param destX la position x de l'image
 * @param destY la position y de l'image
 */
void placerImage(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer, float zoom, float destX, float destY);

/**
 * @brief Joue une animation avec un personnage, un sol et un fond
 * 
 * @param sol la texture du sol
 * @param fond la texture du fond
 * @param perso la planche de vignettes du personnage
 * @param window la fenetre
 * @param renderer le rendu de la fenetre
 */
void animation(SDL_Texture *sol,SDL_Texture * fond, SDL_Texture * perso, SDL_Window * window, SDL_Renderer * renderer);
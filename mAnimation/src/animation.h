#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SDL_Texture* loadTextureFromImage(char *name, SDL_Renderer *renderer);
void displayFrame(SDL_Renderer *renderer, SDL_Texture *texture);
int init(SDL_Renderer **renderer, SDL_Window **window, SDL_Texture **texture);


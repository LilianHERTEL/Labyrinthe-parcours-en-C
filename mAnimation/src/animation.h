#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Texture* loadTextureFromImage(char *name, SDL_Renderer *renderer);
void displayFrame(SDL_Renderer *renderer, int frame);
int init(SDL_Renderer **renderer, SDL_Window **window, SDL_Texture **texture);


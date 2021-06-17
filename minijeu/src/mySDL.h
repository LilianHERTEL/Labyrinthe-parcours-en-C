#pragma once
#include <stdio.h>
#include "bool.h"
#include "SDL2/SDL.h"

bool_t initializeSDL(void);
void quitSDL(char ok,
             char const* msg,
             SDL_Window* window,
             SDL_Renderer* renderer);
void waitForQuitSDL(void);
SDL_Texture* loadTextureFromImage(char *name, SDL_Renderer *renderer);

#pragma once

#include <SDL2/SDL.h>

#define NB 4

void moveWindows(SDL_Window *windows[], int delay);
void createWindows(SDL_Window *windows[]);
void destroyWindows(SDL_Window *windows[]);

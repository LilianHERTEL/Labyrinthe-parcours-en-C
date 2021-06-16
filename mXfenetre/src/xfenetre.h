#pragma once

#include <SDL2/SDL.h>

#define NB 4

typedef enum { false, true } bool;

void moveWindows(SDL_Window *windows[], int delay);
void createWindows(SDL_Window *windows[]);
void destroyWindows(SDL_Window *windows[]);
bool areInScreen(int x[], int y[], SDL_DisplayMode screen);

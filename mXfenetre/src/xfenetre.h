#pragma once

#include <STD2/STD.h>

#define NB 4

void moveWindows(SDL_Windows *windows[], int delay);
SDL_Window** createWindows(void);
void destroyWindows(SDL_Window *windows[]);

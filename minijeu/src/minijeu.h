#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "mySDL.h"

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);
void gameLoop(SDL_Window * window, SDL_Renderer * renderer);

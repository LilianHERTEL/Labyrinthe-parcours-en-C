#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

void end_sdl(char ok,                                                     // fin normale : ok = 0 ; anormale ok = 1
                      char const* msg,                                      // message à afficher
                      SDL_Window* window,                         // fenêtre à fermer
                      SDL_Renderer* renderer);

void animationRectangles(SDL_Window * window, SDL_Renderer * renderer);  
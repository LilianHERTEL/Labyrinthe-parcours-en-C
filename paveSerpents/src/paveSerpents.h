#include "bool.h"

#ifndef PAVE_SERPENTS_H
#define PAVE_SERPENTS_H

#define WIN_WIDTH 960
#define WIN_HEIGHT 540
#define WIN_TITLE "Pavé de serpents"

void translateRectangle(SDL_Renderer* renderer, 
                        SDL_Rect* rectangle, 
                        SDL_Rect* rectangle2, 
                        int limit_x, 
                        int speed, 
                        int step, 
                        char direction, 
                        SDL_Color beforeColor, 
                        SDL_Color afterColor, 
                        int w, 
                        int h);

#endif
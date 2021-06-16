#include <stdio.h>
#include <SDL2/SDL.h>
#include "grid.h"

void drawGrid(SDL_Renderer *renderer, grid_t grid) {
	int i, j, width, height;
	SDL_Rect rectangle;
	
	SDL_GetRendererOutputSize(renderer, &width, &height);
	//SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	rectangle.w = height / grid.x;
	//rectangle.w = 10;
	rectangle.h = height / grid.y;
	//rectangle.h = 10;
	for(i = 0; i < grid.x; ++i) {
		rectangle.x = rectangle.w * i;
		for(j = 0; j < grid.y; ++j) {
			rectangle.y = rectangle.h * j;
			if(grid.grid[i][j]) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			SDL_RenderFillRect(renderer, &rectangle);
		}
	}
	SDL_RenderPresent(renderer);
}

int screenSize(int *h, int* w)
{
    SDL_DisplayMode current;
    int code = 0;

    if(SDL_GetCurrentDisplayMode(0, &current) != 0)
   {
       code = 1;
   }
   else
   {
        *h = current.h;
        *w = current.w;
   }
    return code;
}
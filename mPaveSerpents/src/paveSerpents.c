#include "paveSerpents.h"

int main(int argc, char **argv) {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Rect r1, r2, r3;
	int i, x = 100, y = 100, width = 500, height = 300;

	(void)argc;
	(void)argv;
	
	if(!SDL_Init()) {
		return EXIT_FAILURE;
	}
	window = SDL_CreateWindow("pave de serpents", x, y, width, height, 0);
	if(window == NULL) {
		SDL_Quit();
		return EXIT_FAILURE;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	r1.x = 0;
	r1.y = 0;
	r1.h = height / 5;
	r1.w = width / 10;

	r2.h = height / 5;
	r2.w = width / 10;	
	r2.x = width - r2.w;
	r2.y = 0;
	
	r3.h = height / 5;
	r3.w = width / 10;	
	r3.x = width / 2;
	r3.y = 2 * height / 3;
		
	for(i = 0; i < 1000; ++i) {
		moveSquare1(renderer, r1);
		moveSquare2(renderer, r2);
		moveSquare3(renderer, r3);
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void moveSquare1(SDL_Renderer *renderer, SDL_Rect rect);
void moveSquare2(SDL_Renderer *renderer, SDL_Rect rect);
void moveSquare3(SDL_Renderer *renderer, SDL_Rect rect);

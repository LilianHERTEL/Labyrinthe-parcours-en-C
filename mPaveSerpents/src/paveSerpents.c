#include "paveSerpents.h"

int main(int argc, char **argv) {
	SDL_Renderer *renderer;
	SDL_Window *window;
	int i, x = 100, y = 100, width = 500, height = 300;

	(void)argc;
	(void)argv;
	
	if(!SDL_Init()) {
		return EXIT_FAILURE;
	}
	window = SDL_CreateWindow("pave de serpents", 100, 100, 500, 300, 0);
	if(window == NULL) {
		SDL_Quit();
		return EXIT_FAILURE;
	}
	renderer = SDL_CreateRenderer(window, -1 ,SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	for(i = 0; i < 1000; ++i) {
		moveSquare1(renderer);
		moveSquare2(renderer);
		moveSquare3(renderer);
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void moveSquare1(SDL_Renderer *renderer);
void moveSquare2(SDL_Renderer *renderer);
void moveSquare3(SDL_Renderer *renderer);

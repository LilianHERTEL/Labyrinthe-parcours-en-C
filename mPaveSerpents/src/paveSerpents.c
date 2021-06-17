#include "paveSerpents.h"

int main(int argc, char **argv) {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Rect r1, r2, r3;
	int i, x = 100, y = 100, width = 800, height = 450, delay = 100, n = 100;

	(void)argc;
	(void)argv;
	
	if(SDL_Init(SDL_INIT_VIDEO)) {
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
	
	for(i = 0; i < n; ++i) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		moveSquare1(renderer, &r1);
		moveSquare2(renderer, &r2);
		moveSquare3(renderer, &r3, 20 - i);
		SDL_RenderPresent(renderer);
		SDL_Delay(delay);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void moveSquare1(SDL_Renderer *renderer, SDL_Rect *rect) {
	int w, h, speed = 10;
	
	SDL_GetRendererOutputSize(renderer, &w, &h);
	SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
	rect->x += speed;
	rect->y += speed;
	if(rect->y + rect->h > h) {
		rect->y = 0;
	}
	if(rect->x + rect->w > w) {
		rect->x = 0;
	}
	SDL_RenderFillRect(renderer, rect);
}

void moveSquare2(SDL_Renderer *renderer, SDL_Rect *rect) {
	int w, h, speed = 6;
	
	SDL_GetRendererOutputSize(renderer, &w, &h);
	SDL_SetRenderDrawColor(renderer, (2 * rect->x) % 256, rect->x % 256, (3 * rect->x) % 256, 255);

	rect->x += speed;
	if(rect->x + rect->w > w) {
		rect->x = 0;
	}
	SDL_RenderFillRect(renderer, rect);	
}
void moveSquare3(SDL_Renderer *renderer, SDL_Rect *rect, int speed) {
	int w, h;
	
	SDL_GetRendererOutputSize(renderer, &w, &h);
	SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
	rect->y += speed;
	if(rect->y + rect->h > h) {
		rect->y = 0;
	}
	else if(rect->y < 0) {
		rect->y = h - rect->h;
	}
	SDL_RenderFillRect(renderer, rect);
}

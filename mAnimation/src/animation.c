#include "animation.h"

int main(int argc, char **argv) {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture *texture;
	
	(void)argc;
	(void)argv;	
	
	if(init(&renderer, &window, &texture)) {
		return EXIT_FAILURE;
	}
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	displayFrame(renderer, texture);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}

int init(SDL_Renderer **renderer, SDL_Window **window, SDL_Texture **texture) {
	int x = 500, y = 300, height = 300, width = 500;
	
	if(SDL_Init(0)) {
		fputs("erreur chargement de la SDL\n", stderr);
		return EXIT_FAILURE;
	}
	
	if(IMG_Init(0)) {
		fputs("erreur chargement de SDL_Image\n", stderr);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	*window = SDL_CreateWindow("animation", x, y, width, height, 0);
	if(window == NULL) {
		fputs("erreur creation de la fenetre\n", stderr);
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) {
		fputs("erreur creation du renderer\n", stderr);
		SDL_DestroyWindow(*window);
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	*texture = loadTextureFromImage("../res/cards.png", *renderer);
	if(*texture == NULL) {
		fputs("erreur creation de la texture\n", stderr);
		SDL_DestroyRenderer(*renderer);
		SDL_DestroyWindow(*window);
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	return 0;
}

SDL_Texture* loadTextureFromImage(char *name, SDL_Renderer *renderer) {
	SDL_Texture* texture;
	SDL_Surface* surface;
	
	surface = IMG_Load(name);
	if(surface == NULL) {
		return NULL;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	return texture;
}

void displayFrame(SDL_Renderer *renderer, SDL_Texture *texture) {
	SDL_Rect source = {0}, destination = {0}, window = {0}, card = {0};
	int n = 30, offset_x, offset_y, i, delay = 2000, speed = 10;
	float zoom = 2;

	srand(time(0));
	SDL_GetRendererOutputSize(renderer, &window.w, &window.h);
	SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
	offset_x = source.w / 14;
	offset_y = source.h / 4;
	card.x = 13 * offset_x;
	card.y = 1 * offset_y;
	card.w = offset_x;
	card.h = offset_y;
	destination.w = offset_x * zoom;
	destination.h = offset_y * zoom;
	destination.y = (window.h - destination.h) / 2;
	destination.x = (window.w - destination.w) / 2;
	SDL_RenderCopy(renderer, texture, &card, &destination);
	SDL_RenderPresent(renderer);
	SDL_Delay(delay);
	for(i = 0; i < n; ++i) {
		destination.w = offset_x * zoom;
		destination.h = offset_y * zoom;
		destination.y = ((window.h - destination.h) / 2) + (((i % 3) - 3) * 5);
		destination.x = (window.w - destination.w) / 2;
		card.x = (rand() % 14 * offset_x) % source.w;
		card.y = (rand() % 4 * offset_y) % source.h;
		//printf("x %d, y %d\n", card.x, card.y);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, &card, &destination);
		SDL_RenderPresent(renderer);
		//printf("delay : %d\n", i * 100 / speed + 100);
		SDL_Delay(i * 100 / speed + 100);
	}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, &card, &destination);
	SDL_RenderPresent(renderer);
	SDL_Delay(delay);
}

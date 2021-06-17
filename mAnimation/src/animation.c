#include "animation.h"

int main(int argc, char **argv) {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture *texture;
	int delay = 100;
	
	(void)argc;
	(void)argv;	
	
	
	if(!init(&renderer, &window, &texture)) {
		return EXIT_FAILURE;
	}
	
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}

int init(SDL_Renderer **renderer, SDL_Window **window, SDL_Texture **texture) {
	int x = 100, y = 100, height = 300, width = 500;
	
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
void displayFrame(SDL_Renderer *renderer, int frame);


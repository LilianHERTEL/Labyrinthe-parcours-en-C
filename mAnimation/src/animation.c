#include "animation.h"

int main(int argc, char **argv) {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture *texture;
	
	(void)argc;
	(void)argv;	
	if(SDL_Init(0)) {
		fputs("erreur chargement de la SDL\n", stderr);
		return EXIT_FAILURE;
	}
	
	if(IMG_Init(0)) {
		fputs("erreur chargement de SDL_Image\n", stderr);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}

SDL_Texture* loadTextureFromImage(char *name, SDL_Renderer *renderer);
void displayFrame(SDL_Renderer *renderer, int frame);


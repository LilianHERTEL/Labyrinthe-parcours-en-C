#include <stdio.h>
#include "mySDL.h"
#include <SDL2/SDL_image.h>

void createWindows(SDL_Window* windows[], int nbWindows) {
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);
	int winWidth = display.h/10;
	int winHeight = winWidth;
	int windowsShift = winHeight;
	int i;
	for (i = 0; i < nbWindows; i++) {
		windows[i] = SDL_CreateWindow("Jeu de la vie", (display.w/2 - winWidth/2) + i*windowsShift - (nbWindows*winWidth)/2, (display.h/2 - winHeight/2) + i*windowsShift - (nbWindows*winWidth)/2, winWidth, winHeight, SDL_WINDOW_SHOWN);
		if (windows[i] == NULL) {
			quitSDL(false, "Error : SDL window creation", windows[i], NULL);
		}
	}
}

void moveWindows(SDL_Window* windows[], int nbWindows) {
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);
	int winWidth = display.h/10;
	int winHeight = winWidth;
	int windowsShift = winHeight;
	int i, winPosX, winPosY;
	for (i = 0; i < nbWindows; i++) {
		SDL_GetWindowPosition(windows[i], &winPosX, &winPosY);
		SDL_SetWindowPosition(windows[i], winPosX, (display.h/2 - winHeight/2) - i*windowsShift + (nbWindows*winWidth)/2 - winHeight);
	}
}



SDL_Texture* loadTexture(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) quitSDL(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) quitSDL(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

void showTiles(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* background) {
	SDL_Rect source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};    
	float zoom = 1;
	SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);               // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(background, NULL, NULL, &source.w, &source.h);  // Récupération des dimensions de l'image

	for (int i = 0; i < 10; i++) {
		destination.w = source.w * zoom;         // La destination est un zoom de la source
		destination.h = source.h * zoom;         // La destination est un zoom de la source
    	destination.x = (window_dimensions.w - destination.w) - i*source.w;     // La destination est au milieu de la largeur de la fenêtre
		destination.y = (window_dimensions.h - destination.h);  // La destination est au milieu de la hauteur de la fenêtre

		SDL_RenderCopy(renderer, background, &source, &destination);
	}
	for (int i = 0; i < 4; i++) {
		destination.w = source.w * zoom;         // La destination est un zoom de la source
     	destination.h = source.h * zoom;         // La destination est un zoom de la source
     	destination.x = (window_dimensions.w - destination.w) - i*source.w;     // La destination est au milieu de la largeur de la fenêtre
		 destination.y = (window_dimensions.h - destination.h) - source.h;  // La destination est au milieu de la hauteur de la fenêtre

		SDL_RenderCopy(renderer, background, &source, &destination);

		destination.w = source.w * zoom;         // La destination est un zoom de la source
		destination.h = source.h * zoom;         // La destination est un zoom de la source
		destination.x = (window_dimensions.w - destination.w) - i*source.w;     // La destination est au milieu de la largeur de la fenêtre
    	destination.y = (window_dimensions.h - destination.h) - 2*source.h;  // La destination est au milieu de la hauteur de la fenêtre
		SDL_RenderCopy(renderer, background, &source, &destination);
	}
	destination.w = source.w * zoom;         // La destination est un zoom de la source
	destination.h = source.h * zoom;         // La destination est un zoom de la source
	destination.x = (window_dimensions.w - destination.w) - 4*source.w;     // La destination est au milieu de la largeur de la fenêtre
	destination.y = (window_dimensions.h - destination.h) - 1*source.h;  // La destination est au milieu de la hauteur de la fenêtre

	SDL_RenderCopy(renderer, background, &source, &destination);
}

void animation(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * character, SDL_Texture* ground) {
  SDL_Rect    character_source = {0},                // Rectangle définissant la zone totale de la planche
			  ground_source = {0},
              window_dimensions = {0},     // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
              destination = {0},           // Rectangle définissant où la zone_source doit être déposée dans le renderer
              state = {0};                 // Rectangle de la vignette en cours dans la planche 
  int         offset_y,
              offset_x,
              x,
              speed = 15, 
              nb_images = 9;               // 9 Images sur la premiere ligne de la planche     
  float       zoom = 2;  

  character = loadTexture("player_tilesheet.png", window, renderer);
  ground = loadTexture("dirt_grass.png", window, renderer);

  SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
  SDL_QueryTexture(character, NULL, NULL, &character_source.w, &character_source.h);  
  SDL_QueryTexture(ground, NULL, NULL, &ground_source.w, &ground_source.h);

  // Dimensions de la vignette dans la planche
  offset_x = character_source.w / nb_images, 
  offset_y = character_source.h / 3;
  // Dimensions de la vignette
  state.w = offset_x;             
  state.h = offset_y;             
  // Dimensions du sprite a l'ecran
  destination.w = offset_x * zoom;       
  destination.h = offset_y * zoom;     
  // Position du debut de l'animation 
  destination.y = window_dimensions.h - offset_y*zoom - ground_source.h;

  for (x = 0; x < window_dimensions.w - destination.w; x += speed) {
    destination.x = x;              // Position x de la vignette (elle bouge horizontalement)
	if (x > (window_dimensions.w - destination.w)/2 && x < (window_dimensions.w - destination.w)/2+speed){
		destination.y -= ground_source.h;
	}
	if (x > (window_dimensions.w - destination.w)/2+9*speed && x < (window_dimensions.w - destination.w)/2+10*speed){
		destination.y -= ground_source.h;
	}	
    state.x += offset_x;            // Vignette suivante
    state.x %= character_source.w;            // Pour revenir a la vignette du debut        
    
    SDL_RenderClear(renderer);      
    //placerImage(fond, window, renderer, 3.5, 0 - x*0.8, - window_dimensions.w/2);
    //placerImage(sol, window, renderer, 4, 0 - x * 1.5, window_dimensions.h - 150 );
	showTiles(window, renderer, ground);
    SDL_RenderCopy(renderer, character, &state, &destination);  
    SDL_RenderPresent(renderer);        
    SDL_Delay(80);              
  }
  SDL_RenderClear(renderer);       
}

int main(int argc, char const *argv[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture* ground = NULL;
	SDL_Texture* character = NULL;
	SDL_Texture* sky1 = NULL;
	SDL_Texture* sky2 = NULL;
	
	bool_t status;

	(void)argc;
	(void)argv;

	status = initializeSDL();
	if (!status) quitSDL(false, "Error : SDL initialization", NULL, NULL);

	window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		quitSDL(false, "Error : SDL window creation", window, renderer);
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		quitSDL(false, "Error : SDL renderer creation", window, renderer);
		exit(EXIT_FAILURE);
	}
	
	animation(window, renderer, ground, character, sky1, sky2);
	
	SDL_RenderPresent(renderer);  

	//createWindows(windows, nbWindows);
	//moveWindows(windows, nbWindows);

	SDL_DestroyTexture(ground);
	IMG_Quit();
	quitSDL(true, "SDL END", window, renderer);

	return 0;
}

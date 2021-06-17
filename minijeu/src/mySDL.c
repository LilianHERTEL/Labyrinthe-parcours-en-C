#include <stdio.h>
#include "bool.h"
#include "SDL2/SDL.h"

bool_t initializeSDL(void) {
    bool_t status = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    	status = false; 
	}
	return status;
}

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void quitSDL(bool_t status,
             char const* msg,
             SDL_Window* window,
             SDL_Renderer* renderer) {                
  char msg_formated[255];
  int l;

  if (!status) {
    strncpy(msg_formated, msg, 250);                                 
    l = strlen(msg_formated);                                        
    strcpy(msg_formated + l, " : %s\n");                     
    SDL_Log(msg_formated, SDL_GetError());                   
  }                                                               

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
  if (window != NULL)   SDL_DestroyWindow(window);                                        

  SDL_Quit();                                                     

  if (!status) {
	  exit(EXIT_FAILURE);                                              
  }                                                               
}

void waitForQuitSDL(void) {
  SDL_Event event;
  SDL_bool exit = SDL_FALSE;
  // Attente de la fermeture de la fenêtre
  while(!exit) {
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) exit = SDL_TRUE;    
  }

}

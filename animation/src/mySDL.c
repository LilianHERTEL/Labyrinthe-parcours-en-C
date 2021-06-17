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

void quitSDL(bool_t status,                              // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                            // message à afficher
             SDL_Window* window,                         // fenêtre à fermer
             SDL_Renderer* renderer) {                   // renderer à fermer                           
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
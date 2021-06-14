#include <SDL2/SDL.h>
#include <stdio.h>
#include "paveSerpents.h"
#include "bool.h"


int main(int argc, char const *argv[])
{
  // Création de la fenêtre
  SDL_Window* window = NULL;
  window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    SDL_Log("Erreur de création de la fenêtre - %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //Création du renderer
  SDL_Renderer* renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SDL_Log("Erreur d'initialisation d'un renderer - %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //Met le fond blanc
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_RenderClear(renderer);

  //Création du rectangle
  SDL_Rect rectangle = {0, 0, 100, 100};

  //Change la couleur de rendu à rouge
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  //Dessine le rectangle rouge
  SDL_RenderFillRect( renderer, &rectangle);
  SDL_RenderPresent(renderer);

  SDL_Event event;
  SDL_bool exit = SDL_FALSE;
  // Attente de la fermeture de la fenêtre
  while(!exit) {
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) exit = SDL_TRUE;    
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  
  
  return 0;
}

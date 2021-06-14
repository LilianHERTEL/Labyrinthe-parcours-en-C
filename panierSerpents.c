#include <SDL2/SDL.h>
#include <stdio.h>
#include "panierSerpents.h"
#include "bool.h"

/************************************/
/*  exemple de création de fenêtres */
/************************************/

void test() {
    SDL_Window *window_1 = NULL,               // Future fenêtre de gauche
      *window_2 = NULL;                      // Future fenêtre de droite

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  /* Création de la fenêtre de gauche */
  window_1 = SDL_CreateWindow(
      "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      400, 300,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);                 // redimensionnable

  if (window_1 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  /* Création de la fenêtre de droite */
  window_2 = SDL_CreateWindow(
      "Fenêtre à droite",                    // codage en utf8, donc accents possibles
      400, 0,                                // à droite de la fenêtre de gauche
      500, 300,                              // largeur = 500, hauteur = 300
      0);

  if (window_2 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(2000);                           // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
  SDL_DestroyWindow(window_2);
  SDL_DestroyWindow(window_1);

  SDL_Quit();
}

bool createRenderer(SDL_Window* window, SDL_Renderer* renderer) {
  bool return_status = EXIT_SUCCESS;
  //SDL_Renderer *renderer = NULL;

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SDL_Log("Erreur d'initialisation d'un renderer - %s\n", SDL_GetError());
    return_status = EXIT_SUCCESS;
  }
  return return_status;
}

bool testWindow(void) {
    bool error = EXIT_FAILURE;
    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erreur d'initialisation de la SDL - %s\n", SDL_GetError());
        //return_status = EXIT_FAILURE;
    }
    else {
      window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
      if (window == NULL) {
        SDL_Log("Erreur de création de la fenêtre - %s\n", SDL_GetError());
        //return_status = EXIT_FAILURE;
      }
      else {
        error = createRenderer(window, renderer);

        //Configuration de la couleur de dessin
        if(!error) {
          SDL_Color red = {255, 0, 0, 255};
          if (SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a) != 0) {
            SDL_Log("Erreur de création de la couleur - %s\n", SDL_GetError());
            error = EXIT_FAILURE
          }
          if (SDL_RenderClear(renderer)) {
            SDL_Log("Erreur de changement de la couleur - %s\n", SDL_GetError());
          }

          // Création d'un rectangle
          SDL_Rect rect = {10, 10, 10, 10};
          SDL_RenderFillRect(renderer, &rect);
          SDL_RenderPresent(renderer);
        }

        SDL_Delay(5000);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
      }
    }

    
    
    SDL_Quit();

    return error;
}

int main(int argc, char const *argv[])
{
    return testWindow();
}

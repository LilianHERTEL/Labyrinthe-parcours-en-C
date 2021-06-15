#include <SDL2/SDL.h>
#include <stdio.h>
#include "paveSerpents.h"
#include "bool.h"
#include "color.h"

void translateRectangle(SDL_Renderer* renderer, SDL_Rect* rectangle, int limit_x, int speed, int step, char direction, SDL_Color beforeColor, SDL_Color afterColor) {
  SDL_Rect new_rect = *rectangle;
  int i;
  for (i = 0; i < limit_x; i++) {
    int r = beforeColor.r == 255 ? 255-(255*i/limit_x) : afterColor.r*i/limit_x;
    int g = beforeColor.g == 255 ? 255-(255*i/limit_x) : afterColor.g*i/limit_x;
    int b = beforeColor.b == 255 ? 255-(255*i/limit_x) : afterColor.b*i/limit_x;
    //Met le fond blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    if (direction == 'x') new_rect.x = new_rect.x + step*speed;
    else new_rect.y = new_rect.y + step*speed;

    printf("%d\n", r);
    
    //Change la couleur de rendu à rouge
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    //Dessine le rectangle rouge
    SDL_RenderFillRect(renderer, &new_rect);
    SDL_RenderPresent(renderer);
    //SDL_Delay(200);
  }
  *rectangle = new_rect;
  SDL_Delay(500);
}

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

  int winWidth;
  int winHeight;
  SDL_GetWindowSize(window, &winWidth, &winHeight);
  //Création du rectangle
  SDL_Rect rectangle = {0, 0, winWidth/10, winHeight/10};

  //Change la couleur de rendu à rouge
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  //Dessine le rectangle rouge
  SDL_RenderFillRect( renderer, &rectangle);
  SDL_RenderPresent(renderer);

  SDL_Delay(1000);

  int step = 1;
  int speed = 6;
  int i;
  int limit_x;
  //SDL_GetWindowSize(window, &limit_x, NULL);
  //printf("%d\n", limit_x);
  limit_x = (winWidth - rectangle.w)/speed;

  int limit_y;
  //SDL_GetWindowSize(window, NULL, &limit_y);
  //printf("%d\n", limit_y);
  limit_y = (winHeight - rectangle.h)/speed;
  /*
  printf("%d\n", limit_x);
  for (i = 0; i < limit_x; i++){
    //Met le fond blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    rectangle.x = rectangle.x + step*speed;
    //Change la couleur de rendu à rouge
    SDL_SetRenderDrawColor(renderer, 255*i/limit_x, 0, 0, 255);
    //Dessine le rectangle rouge
    SDL_RenderFillRect( renderer, &rectangle);
    SDL_RenderPresent(renderer);
    //SDL_Delay(200);
  }
  int j;
  int limit_y;
  SDL_GetWindowSize(window, NULL, &limit_y);
  printf("%d\n", limit_y);
  limit_y = (limit_y - rectangle.h)/speed;
  printf("%d\n", limit_y);
  for (j = 0; j < limit_y; j++) {
    //Met le fond blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    rectangle.y = rectangle.y + step*speed;
    //Change la couleur de rendu à rouge
    SDL_SetRenderDrawColor(renderer, 255-(255*j/limit_y), 255*j/limit_y, 0, 255);
    //Dessine le rectangle rouge
    SDL_RenderFillRect( renderer, &rectangle);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }

  step = -step;
  SDL_GetWindowSize(window, &limit_x, NULL);
  printf("%d\n", limit_x);
  limit_x = (limit_x - rectangle.w)/speed;
  printf("%d\n", limit_x);
  for (i = 0; i < limit_x; i++){
    //Met le fond blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    rectangle.x = rectangle.x + step*speed;
    //Change la couleur de rendu à rouge
    SDL_SetRenderDrawColor(renderer, 255*i/limit_x, 0, 0, 255);
    //Dessine le rectangle rouge
    SDL_RenderFillRect( renderer, &rectangle);
    SDL_RenderPresent(renderer);
    //SDL_Delay(200);
  }
  SDL_GetWindowSize(window, NULL, &limit_y);
  printf("%d\n", limit_y);
  limit_y = (limit_y - rectangle.h)/speed;
  printf("%d\n", limit_y);
  for (j = 0; j < limit_y; j++) {
    //Met le fond blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    rectangle.y = rectangle.y + step*speed;
    //Change la couleur de rendu à rouge
    SDL_SetRenderDrawColor(renderer, 255-(255*j/limit_y), 255*j/limit_y, 0, 255);
    //Dessine le rectangle rouge
    SDL_RenderFillRect( renderer, &rectangle);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }
  */
  SDL_Color beforeColor = {0,0,0,0};
  SDL_Color afterColor = {255,0,0,0};
  translateRectangle(renderer, &rectangle, limit_x, speed, step, 'x', beforeColor, afterColor);
  beforeColor = afterColor;
  afterColor.r = 0;
  afterColor.g = 255;
  translateRectangle(renderer, &rectangle, limit_y, speed, step, 'y', beforeColor, afterColor);
  beforeColor = afterColor;
  afterColor.g = 0;
  afterColor.b = 255;
  step = -step;
  translateRectangle(renderer, &rectangle, limit_x, speed, step, 'x', beforeColor, afterColor);
  beforeColor = afterColor;
  afterColor.b = 0;
  translateRectangle(renderer, &rectangle, limit_y, speed, step, 'y', beforeColor, afterColor);

  SDL_Delay(1000);

  SDL_RenderClear(renderer);
  rectangle.x = rectangle.x + 100;


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

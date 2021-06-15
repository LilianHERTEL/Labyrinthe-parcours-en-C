#include <SDL2/SDL.h>
#include <stdio.h>
#include "paveSerpents.h"
#include "bool.h"
#include "color.h"

void translateRectangle(SDL_Renderer* renderer, SDL_Rect* rectangle, SDL_Rect* rectangle2, int limit_x, int speed, int step, char direction, SDL_Color beforeColor, SDL_Color afterColor, int w, int h) {
  SDL_Rect new_rect1 = *rectangle;
  SDL_Rect new_rect2 = *rectangle2;
  int i;
  int limit_1 = (w - new_rect1.w)/speed;
  int limit_2_w = (w - 3*new_rect2.w)/speed;
  int limit_2_h = (h - 3*new_rect2.h)/speed;
  for (i = 0; i < limit_x; i++) {
    int r = beforeColor.r == 255 ? 255-(255*i/limit_1) : afterColor.r*i/limit_1;
    int g = beforeColor.g == 255 ? 255-(255*i/limit_1) : afterColor.g*i/limit_1;
    int b = beforeColor.b == 255 ? 255-(255*i/limit_1) : afterColor.b*i/limit_1;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    if (direction == 'x') {
      new_rect1.x = new_rect1.x + step*speed;
      if (i <= limit_2_w) new_rect2.x = new_rect2.x - step*speed;
    }
    else {
      new_rect1.y = new_rect1.y + step*speed;
      if (i <= limit_2_h) new_rect2.y = new_rect2.y + step*speed;
    }
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &new_rect1);

    SDL_RenderFillRect(renderer, &new_rect2);
    SDL_RenderPresent(renderer);
  }
  *rectangle = new_rect1;
  *rectangle2 = new_rect2;
}

int main(void)
{
  // Création de la fenêtre
  SDL_Window* window = NULL;
  window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    SDL_Log("Erreur de création de la fenêtre - %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Création du renderer
  SDL_Renderer* renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SDL_Log("Erreur d'initialisation d'un renderer - %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Met le fond blanc
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  int winWidth;
  int winHeight;
  SDL_GetWindowSize(window, &winWidth, &winHeight);

  // Création des rectangles
  SDL_Rect rectangle = {0, 0, winWidth/5, winHeight/5};
  SDL_Rect rectangle2 = {winWidth-2*winWidth/5,winHeight/5, winWidth/5, winHeight/5};

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect( renderer, &rectangle);
  SDL_RenderFillRect( renderer, &rectangle2);
  SDL_RenderPresent(renderer);
  SDL_Delay(1000);

  int step = 1;
  int speed = 12;
  int limit_x;
  limit_x = (winWidth - rectangle.w)/speed;

  int limit_y;
  limit_y = (winHeight - rectangle.h)/speed;

  SDL_Color beforeColor = {0,0,0,0};
  SDL_Color afterColor = {255,0,0,0};
  translateRectangle(renderer, &rectangle, &rectangle2, limit_x, speed, step, 'x', beforeColor, afterColor, winWidth, winHeight);
  beforeColor = afterColor;
  afterColor.r = 0;
  afterColor.g = 255;
  translateRectangle(renderer, &rectangle, &rectangle2, limit_y, speed, step, 'y', beforeColor, afterColor, winWidth, winHeight);
  beforeColor = afterColor;
  afterColor.g = 0;
  afterColor.b = 255;
  step = -step;
  translateRectangle(renderer, &rectangle, &rectangle2, limit_x, speed, step, 'x', beforeColor, afterColor, winWidth, winHeight);
  beforeColor = afterColor;
  afterColor.b = 0;
  translateRectangle(renderer, &rectangle, &rectangle2, limit_y, speed, step, 'y', beforeColor, afterColor, winWidth, winHeight);

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

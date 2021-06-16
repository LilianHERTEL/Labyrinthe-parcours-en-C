#include "snake.h"

void end_sdl(char ok,                                                     // fin normale : ok = 0 ; anormale ok = 1
                      char const* msg,                                      // message à afficher
                      SDL_Window* window,                         // fenêtre à fermer
                      SDL_Renderer* renderer)                      // renderer à fermer
{                           
  char msg_formated[255];                                         
  int l;                                                          

  if (!ok) 
  {                                                      
         strncpy(msg_formated, msg, 250);                                 
         l = strlen(msg_formated);                                        
         strcpy(msg_formated + l, " : %s\n");                     
         SDL_Log(msg_formated, SDL_GetError());                   
  }                                                               

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
  if (window != NULL)   SDL_DestroyWindow(window);                                        

  SDL_Quit();                                                     

  if (!ok) {                                                      
         exit(EXIT_FAILURE);                                              
  }                                                               
}

void animationRectangles(SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_Rect  window_dimensions = {0},
                       r1 = {0},
                       r2 = {0},
                       r3 = {0};
    int              pasXr1 = 35,
                      pasYr1 = 25, 
                      green1 = 255,
                      pasR3 = 50;

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);      
    
    r1.w = r1.h = window_dimensions.h/4;
    r1.x = (window_dimensions.w - r1.w)/2; 
    r1.y = (window_dimensions.h - r1.w)/2;

    r2.w = r2.h = window_dimensions.h/3;

    r3.w = r3.h = window_dimensions.h/7;
    r3.y = (window_dimensions.h - r3.w)/2;

    for(int i = 0; i< 200 ; i++)
    {
        if(! (r1.x + r1.w + pasXr1 <= window_dimensions.w && r1.x >= 0))
        {
            pasXr1 = -pasXr1;
            green1 = (green1 -30)%255;
        }
        if(! (r1.y + r1.h + pasYr1 <= window_dimensions.h && r1.y >= 0))
        { 
            pasYr1 = -pasYr1; 
            green1 = (green1 -25)%255;
        }
        if(! (r3.x + r3.w + pasR3 <= window_dimensions.w && r3.x >= 0))
            pasR3 = -pasR3;

        r1.x = r1.x + pasXr1 ;
        r1.y = r1.y + pasYr1 ;

        r2.x = (r2.x + 40 ) % window_dimensions.w ;
        r2.y = (r2.y + 36) % window_dimensions.h ;
       
        r3.x = (r3.x + pasR3) ;
       
        SDL_SetRenderDrawColor(renderer,65, green1, 0,255);
        SDL_RenderFillRect(renderer, &r1);
        SDL_SetRenderDrawColor(renderer,255, 255, 0,255);
        SDL_RenderFillRect(renderer, &r2);
         SDL_SetRenderDrawColor(renderer,255, 0, 0,255);
        SDL_RenderFillRect(renderer, &r3);
        SDL_SetRenderDrawColor(renderer,255, 255, 255,255);
        
        SDL_RenderPresent(renderer);    
        SDL_Delay(40);
        SDL_RenderClear(renderer);
    }
}

int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;

    /* INITIALISATIONS */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(1, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    window = SDL_CreateWindow("Animation",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED, 
                        screen.w * 0.8,
                        screen.h * 0.8,
                        SDL_WINDOW_RESIZABLE);
    if (window == NULL) end_sdl(1, "ERROR WINDOW CREATION", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(1, "ERROR RENDERER CREATION", window, renderer);

    /*TRAITEMENT*/

    animationRectangles(window, renderer);

    end_sdl(0, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}
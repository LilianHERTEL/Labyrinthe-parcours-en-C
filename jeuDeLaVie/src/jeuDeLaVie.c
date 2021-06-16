#include "jeuDeLaVie.h"

/*void end_sdl(char ok,                                                     // fin normale : ok = 0 ; anormale ok = 1
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

void drawGrid(SDL_Window * window, SDL_Renderer *renderer, int ** grille, int n, int m) 
{
	int               i,
                      j,
                      poseX,
                      poseY;
	SDL_Rect          window_dimensions = {0},
                      rectangle;
	
	SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); 

	rectangle.w = window_dimensions.h / m ;
	rectangle.h = window_dimensions.h / n ;
    poseX = (window_dimensions.w - rectangle.w * m) / 2 ;
    poseY = (window_dimensions.h - rectangle.h * n) / 2 ;

	for(i = 0; i < n; i++) {
		rectangle.x = poseX + rectangle.w * i;
		for(j = 0; j < m; j++) {
			rectangle.y = poseY + rectangle.h * j;
            if(grille[i][j] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
			//SDL_SetRenderDrawColor(renderer, grille[i][j] * 255, grille[i][j] *255, grille[i][j] *255, 255);
			SDL_RenderFillRect(renderer, &rectangle);
		}
	}
	SDL_RenderPresent(renderer);
}*/


int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    /*SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;*/

    /* INITIALISATIONS */
    /*if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(1, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    window = SDL_CreateWindow("Jeu de la vie",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED, 
                        screen.w * 0.8,
                        screen.h * 0.8,
                        SDL_WINDOW_RESIZABLE);
    if (window == NULL) end_sdl(1, "ERROR WINDOW CREATION", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(1, "ERROR RENDERER CREATION", window, renderer);*/

    /*TRAITEMENT*/

    int **grid,
             n = 3,
             m = 3;
    //int i, iterations = 20;
    rule_t *rule;

    rule = malloc(sizeof(rule_t));
	if(rule) {
		
        initLife(rule);	

        grid = allocGrid(n,m);
        if(grid)
        {
            grid = createRandomGrid(grid, n, m);
            displayGrid(grid, n, m);

            //drawGrid(window, renderer, grid, n, m);
            printf("\n\n");
            //SDL_Delay(1000);
            nextIteration(&grid, n, m, rule);
            displayGrid(grid, n, m);
            //drawGrid(window, renderer, grid, n, m);
            
            /*for(i = 0; i < iterations; ++i) {
                nextIteration(&grid, n, m, rule);
                drawGrid(window, renderer, grid, n, m);
                //displayGrid(grid, n, m);
                SDL_Delay(300);
            }*/

            //SDL_Delay(1000);
            free(rule);
            freeGrid(grid, n);
        }
    }

    //end_sdl(0, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}

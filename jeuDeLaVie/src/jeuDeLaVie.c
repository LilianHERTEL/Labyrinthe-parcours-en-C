#include "jeuDeLaVie.h"

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer)
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
}


/**
 * @brief Affiche une matrice d'entiers dans la fenetre
 * 
 * @param window 
 * @param renderer 
 * @param grille 
 * @param n 
 * @param m 
 */
void drawGrid(SDL_Window * window, SDL_Renderer *renderer, int ** grille, int n, int m) 
{
	int               i,
                      j,
                      poseX,
                      poseY;
	SDL_Rect          window_dimensions = {0},
                      rectangle;
	
	SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); 

    SDL_SetRenderDrawColor(renderer, 150, 150, 255, 0);
	SDL_RenderClear(renderer);

	rectangle.w = window_dimensions.h / m ;
	rectangle.h = window_dimensions.h / n ;
    poseX = (window_dimensions.w - rectangle.w * m) / 2 ;
    poseY = (window_dimensions.h - rectangle.h * n) / 2 ;

	for(i = 0; i < n; i++) {
		rectangle.y = poseY + rectangle.h * i;
		for(j = 0; j < m; j++) {
			rectangle.x = poseX + rectangle.w * j;
            
            SDL_SetRenderDrawColor(renderer, !grille[i][j] * 255, !grille[i][j] * 255, !grille[i][j] * 255, 255);
			SDL_RenderFillRect(renderer, &rectangle);
		}
	}
	SDL_RenderPresent(renderer);
}

/**
 * @brief Affiche une execution du jeu de la vie
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window      * window = NULL;
    SDL_Renderer    * renderer = NULL;
    SDL_DisplayMode   screen;
    int ** grid,
                      i,
                      n = 50,
                      m = 50,
                      iterations = 30;
    rule_t          * rule;

    /* INITIALISATIONS */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        end_sdl(0, "ERROR SDL INIT", window, renderer);
        exit(EXIT_FAILURE); 
    }

    if(SDL_GetCurrentDisplayMode(0, &screen) != 0)
    {
        end_sdl(0, "ERROR GET_DISPLAY_MODE", window, renderer);
        exit(EXIT_FAILURE); 
    }

    window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                screen.w * 0.8, screen.h * 0.8, SDL_WINDOW_RESIZABLE);
    if (window == NULL) 
    {
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
        exit(EXIT_FAILURE); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
    {
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
        exit(EXIT_FAILURE); 
    }

    /*TRAITEMENT*/

    rule = malloc(sizeof(rule_t));
	if(rule) 
    {
        grid = allocGrid(n,m);
        if(grid)
        {
            grid = createRandomGrid(grid, n, m);
            drawGrid(window, renderer, grid, n, m);

            initLife(rule);	
            for(i = 0; i < iterations; ++i) {
                nextIteration(&grid, n, m, rule);
                drawGrid(window, renderer, grid, n, m);
                SDL_Delay(100);
            }
            SDL_Delay(1000);

            initMaze(rule);	
            for(i = 0; i < iterations; ++i) {
                nextIteration(&grid, n, m, rule);
                drawGrid(window, renderer, grid, n, m);
                SDL_Delay(100);
            }
            SDL_Delay(1000);

            free(rule);
            freeGrid(grid, n);
        }
    }

    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}

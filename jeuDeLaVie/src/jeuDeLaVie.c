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

void gameLoop(SDL_Window * window, SDL_Renderer * renderer, int ** grid, int n, int m, rule_t * rule)
{
    SDL_bool  program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
              paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    while (program_on) 
    {                                   // La boucle des évènements
        SDL_Event event;                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) 
        {                               // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) 
            {                               
            case SDL_QUIT:                             
                program_on = SDL_FALSE;                   
                break;
            case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                                            // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                            // l'event, plusieurs champs deviennent pertinents   
                switch (event.key.keysym.sym) 
                {             // la touche appuyée est ...
                    case SDLK_p:                                // 'p'
                    case SDLK_SPACE:                            // 'SPC'
                        paused = !paused;                         // basculement pause/unpause
                        break;
                    case SDLK_ESCAPE:                           // 'ESCAPE'  
                    case SDLK_q:                                // 'q'
                        program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                                     
                        break;
                    default:                                    // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:                     // Click souris   
                if (SDL_GetMouseState(NULL, NULL) & 
                    SDL_BUTTON(SDL_BUTTON_LEFT) ) {         // Si c'est un click gauche
                    //change_state(state, 1, window);           // Fonction à éxécuter lors d'un click gauche
                } 
                else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT) ) 
                { // Si c'est un click droit
                    //change_state(state, 2, window);           // Fonction à éxécuter lors d'un click droit
                }
                break;
                default:                                      // Les évènements qu'on n'a pas envisagé
                    break;
            }
        }
        drawGrid(window, renderer, grid, n, m);          // On redessine
        if (!paused) 
        {                                  // Si on n'est pas en pause
            nextIteration(&grid, n, m, rule);             // la vie continue... 
        }
        SDL_Delay(50);                                  // Petite pause
    }
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

    SDL_Window       * window = NULL;
    SDL_Renderer     * renderer = NULL;
    SDL_DisplayMode    screen;
    int             ** grid,
                       n = 50,
                       m = 50;
    rule_t           * rule;

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
            initMaze(rule);	

            gameLoop(window, renderer, grid, n, m, rule);

            free(rule);
            freeGrid(grid, n);
        }
    }

    end_sdl(0, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}

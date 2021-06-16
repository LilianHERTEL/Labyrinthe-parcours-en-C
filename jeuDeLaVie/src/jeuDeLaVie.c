#include "jeuDeLaVie.h"

/**
 * @brief Termine en quittant la sdl
 * 
 * @param ok 
 * @param msg 
 * @param window 
 * @param renderer 
 */
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

void gameLoop(SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_bool
    program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
    paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    while (program_on) 
    {                              // La boucle des évènements
        SDL_Event event;                                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) 
        {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
        switch (event.type) 
        {                         // En fonction de la valeur du type de cet évènement
        case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
            program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
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
            change_state(state, 1, window);           // Fonction à éxécuter lors d'un click gauche
            } else if (SDL_GetMouseState(NULL, NULL) & 
                        SDL_BUTTON(SDL_BUTTON_RIGHT) ) { // Si c'est un click droit
            change_state(state, 2, window);           // Fonction à éxécuter lors d'un click droit
            }
            break;
        default:                                      // Les évènements qu'on n'a pas envisagé
            break;
        }
        }
        draw(state, &color, renderer, window);          // On redessine
        if (!paused) 
        {                                  // Si on n'est pas en pause
        next_state(state, survive, born);             // la vie continue... 
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

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;

    /* INITIALISATIONS */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(1, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    window = SDL_CreateWindow("Jeu de la vie",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED, 
                        screen.w * 0.8,
                        screen.h * 0.8,
                        SDL_WINDOW_RESIZABLE);
    if (window == NULL) end_sdl(1, "ERROR WINDOW CREATION", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(1, "ERROR RENDERER CREATION", window, renderer);

    /*TRAITEMENT*/

    int **grid,
             n = 50,
             m = 50;
    int i, iterations = 30;
    rule_t *rule;

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

    end_sdl(0, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}

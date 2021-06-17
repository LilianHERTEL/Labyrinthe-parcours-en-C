#include "minijeu.h"

/**
 * @brief Boucle de jeu du casse-briques
 * 
 * @param window 
 * @param renderer 
 * @param grid 
 * @param n 
 * @param m 
 * @param rule 
 */
void gameLoop(SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_bool  program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
              paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    SDL_Rect  mouse = {0};
              //cell = {0};

    // Initialisation des coordonnees
    //cellDimensions(window, &cell, n, m);

    while (program_on) 
    {                                   // La boucle des évènements
        SDL_Event event;                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) 
        {                               // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) 
            {      
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        // Calcul des dimensions d'une cellule quand la fenetre change de taille
                        //cellDimensions(window, &cell, n, m);
                    }
                    break;
                case SDL_QUIT:                         
                    program_on = 0;                   
                    break;
                case SDL_KEYDOWN:                              
                    switch (event.key.keysym.sym) 
                    {             
                        case SDLK_LEFT:                                // 'fleche gauche'
                        	//bouger la plateforme a gauche
                        	break;
                        case SDLK_RIGHT:
                        	//bouger la plateforme a droite
                        	break;
                        case SDLK_SPACE:                            // 'SPC'
                            paused = !paused;                       // basculement pause/unpause
                            break;
                        case SDLK_ESCAPE:                           // 'ESCAPE'  
                        case SDLK_q:                                // 'q'
                            program_on = 0;                                                         
                            break;
                        default:                      
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:     
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    //Calcul des coordonnees par rapport a l'emplacement du labyrinthe
                    //mouse.x = (mouse.x - cell.x) / cell.w;
                    //mouse.y = (mouse.y - cell.y) / cell.h;
                    if (SDL_BUTTON(SDL_BUTTON_LEFT) ) 
                    {                       
                        //change_state(&grid, n, m, mouse.x, mouse.y);
                    } 
                    else if (SDL_BUTTON(SDL_BUTTON_RIGHT) ) 
                    {                                           
                        //change_state(&grid, n, m, mouse.x, mouse.y);          
                    }
                    break;
                default:                                            
                    break;
            }
        }
        // Changement du fond en fonction de la position de la souris
        SDL_GetMouseState(&mouse.x, &mouse.y);
        SDL_SetRenderDrawColor(renderer, (mouse.x/3) % 255, ((mouse.x + mouse.y) / 3) % 255, (mouse.y/3) % 255, 255);
	    SDL_RenderClear(renderer);

        //drawGrid(renderer, grid, n, m, cell);        
        if (!paused) 
        {      
            SDL_RenderPresent(renderer);                            
            //nextIteration(&grid, n, m, rule);             // la vie continue... 
        }
        SDL_Delay(50);                                  
    }
}

/**
 * @brief Affiche le casse-briques
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

    /* INITIALISATIONS */

    if (initializeSDL() == false) 
    {
        quitSDL(0, "ERROR SDL INIT", window, renderer);
        exit(EXIT_FAILURE); 
    }

    if(SDL_GetCurrentDisplayMode(0, &screen) != 0)
    {
        quitSDL(0, "ERROR GET_DISPLAY_MODE", window, renderer);
        exit(EXIT_FAILURE); 
    }

    window = SDL_CreateWindow("Minijeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                screen.w * 0.8, screen.h * 0.8, SDL_WINDOW_RESIZABLE);
    if (window == NULL) 
    {
        quitSDL(0, "ERROR WINDOW CREATION", window, renderer);
        exit(EXIT_FAILURE); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
    {
        quitSDL(0, "ERROR RENDERER CREATION", window, renderer);
        exit(EXIT_FAILURE); 
    }

    /*TRAITEMENT*/

    gameLoop(window, renderer);

    quitSDL(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}

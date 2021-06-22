#include "labyrintheVue.h"

/**
 * @brief Programme principal - Affiche un labyrinthe
 * 
 * @param argc 
 * @param argv 
 * @return int
 */
int main(int argc, char const *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;

    (void)argc;
    (void)argv;

                /*****INITIALISATION*****/
    if (!initializeSDL())
    {
        quitSDL(false, "Error : SDL initialization", window, renderer);
        exit(EXIT_FAILURE);
    }

    if (SDL_GetCurrentDisplayMode(0, &screen) != 0)
    {
        quitSDL(false, "ERROR GET_DISPLAY_MODE", window, renderer);
        exit(EXIT_FAILURE);
    }

    // Création de la fenetre
    window = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w * 0.8, screen.h * 0.8, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        quitSDL(false, "Error : SDL window creation", window, renderer);
        exit(EXIT_FAILURE);
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        quitSDL(false, "Error : SDL renderer creation", window, renderer);
        exit(EXIT_FAILURE);
    }

                /*****TRAITEMENT*****/

    int i, j;
    int n = 3, m =4;
    int tab[3][4] = {{1, 2, 8, 9},
                        {8, 4, 1, 2},
                        {2, 6, 15, 15}};
    int ** grille;

    grille = (int**)malloc(sizeof(int*)*n);
    for(i=0; i<m; i++)
        grille[i] = (int*)malloc(sizeof(int));

    for(i=0; i<n; i++)
    {
        for(j = 0; j<m; j++)
        {
            grille[i][j] = tab[i][j];
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    drawLab(window, renderer, grille, n, m);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);

    quitSDL(true, "SDL END", window, renderer);

    return 0;
}

void drawLab(SDL_Window * window, SDL_Renderer * renderer, int ** grille, int n, int m)
{
    SDL_Rect positionLab = {0},
             window_dimensions = {0}, 
             tile = {0};
    int      a,
             b,
             i = 0,
             j = 0;

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    a = window_dimensions.h * 0.9;
    b = window_dimensions.w * 0.9;
    positionLab.h = positionLab.w = a <= b ? a : b;
    positionLab.x = (window_dimensions.w - positionLab.w) /2;
    positionLab.y = (window_dimensions.h - positionLab.h) /2;

    tile.w = positionLab.w / m;
    tile.h = positionLab.h / n;

    for(i = 0; i < n; i++) {
		tile.y = positionLab.x + tile.h * i;
		for(j = 0; j < m; j++) {
			tile.x = positionLab.y + tile.w * j;
            SDL_SetRenderDrawColor(renderer, 255, 60, 20, 255);
			SDL_RenderFillRect(renderer, &tile);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            if(grille[i][j] & NORD) // TODO faire des rectangles au lieu de lignes
            {
                SDL_RenderDrawLine(renderer, 
                                    tile.x, 
                                    tile.y, 
                                    tile.x + tile.w, 
                                    tile.y);
            }
            if(grille[i][j] & SUD)
            {
                SDL_RenderDrawLine(renderer, 
                                    tile.x, 
                                    tile.y + tile.h, 
                                    tile.x + tile.w, 
                                    tile.y + tile.h);
            }
            if(grille[i][j] & EST)
            {
                SDL_RenderDrawLine(renderer, 
                                    tile.x + tile.w, 
                                    tile.y, 
                                    tile.x + tile.w, 
                                    tile.y + tile.h);
            }
            if(grille[i][j] & OUEST)
            {
                SDL_RenderDrawLine(renderer, 
                                    tile.x, 
                                    tile.y, 
                                    tile.x, 
                                    tile.y + tile.h);
            }
		}
	}

}
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
    SDL_Texture * wallTexture,
                * groundTexture;

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

    wallTexture = loadTextureFromImage("../images/textures.png", renderer);
    if(wallTexture == NULL) {
        quitSDL(0, " error texture\n", window, renderer);
        exit(EXIT_FAILURE);
    }

    groundTexture = loadTextureFromImage("../images/textures2.png", renderer);
    if(groundTexture == NULL) {
        quitSDL(0, " error texture\n", window, renderer);
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
    for(i=0; i<n; i++)
        grille[i] = (int*)malloc(sizeof(int)*m) ;

    for(i=0; i<n; i++)
    {
        for(j = 0; j<m; j++)
        {
            grille[i][j] = tab[i][j];
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    drawLab(window, renderer, grille, n, m, wallTexture, groundTexture);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

    quitSDL(true, "SDL END", window, renderer);

    return 0;
}

void drawLab(SDL_Window * window, SDL_Renderer * renderer, int ** grille, int n, int m, SDL_Texture * wallTexture, SDL_Texture * groundTexture)
{
    SDL_Rect positionLab = {0},
             window_dimensions = {0}, 
             tile = {0},
             wall = {0},
             wallSource = {0},
             groundSource = {0};
    int      a,
             b,
             i = 0,
             j = 0;

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    wallSource.x = 128;
    wallSource.y = 128;

    groundSource.h = 128;
    groundSource.w = 128;

    a = window_dimensions.h ;
    b = window_dimensions.w ;
    positionLab.h = positionLab.w = a <= b ? a : b;

    a = positionLab.w / m;
    b = positionLab.h / n;
    tile.w = tile.h = a <= b ? a : b;

    positionLab.x = (window_dimensions.w - tile.w * m ) /2;
    positionLab.y = (window_dimensions.h - tile.h * n ) /2;

    //SDL_SetRenderDrawColor(renderer, 220, 60, 20, 255);
	//SDL_RenderFillRect(renderer, &positionLab);

    for(i = 0; i < n; i++) {
		tile.y = positionLab.y + tile.h * i;
		for(j = 0; j < m; j++) {
			tile.x = positionLab.x + tile.w * j;
            SDL_RenderCopy(renderer, groundTexture, &groundSource, &tile);
            if(grille[i][j] & NORD)
            {
                wallSource.h = 128 / 2;
                wallSource.w = 128;
                
                wall.x = tile.x - (tile.w * 0.1)/2;
                wall.y = tile.y - (tile.h * 0.1)/2;
                wall.w = tile.w + (tile.w * 0.1);
                wall.h = tile.h * 0.1;
                SDL_RenderFillRect(renderer, &wall);
                SDL_RenderCopy(renderer, wallTexture, &wallSource, &wall);
            }
            if(grille[i][j] & SUD)
            {
                wallSource.h = 128 / 2;
                wallSource.w = 128;
                
                wall.x = tile.x - (tile.w * 0.1)/2;
                wall.y = tile.y + tile.h - (tile.h * 0.1)/2;
                wall.w = tile.w + (tile.h * 0.1);
                wall.h = tile.h * 0.1;
                SDL_RenderFillRect(renderer, &wall);
                SDL_RenderCopy(renderer, wallTexture, &wallSource, &wall);
            }
            if(grille[i][j] & EST)
            {
                wallSource.h = 128;
                wallSource.w = 128 / 2;
                
                wall.x = tile.x + tile.w - (tile.w * 0.1)/2;
                wall.y = tile.y - (tile.h * 0.1)/2;
                wall.w = tile.w * 0.1;
                wall.h = tile.h + (tile.h * 0.1);
                SDL_RenderFillRect(renderer, &wall);
                SDL_RenderCopy(renderer, wallTexture, &wallSource, &wall);
            }
            if(grille[i][j] & OUEST)
            {
                wallSource.h = 128;
                wallSource.w = 128 / 2;

                wall.x = tile.x - (tile.w * 0.1)/2;
                wall.y = tile.y - (tile.h * 0.1)/2;
                wall.w = tile.w * 0.1;
                wall.h = tile.h + (tile.h * 0.1);
                SDL_RenderFillRect(renderer, &wall);
                SDL_RenderCopy(renderer, wallTexture, &wallSource, &wall);
            }
            
		}
	}

}

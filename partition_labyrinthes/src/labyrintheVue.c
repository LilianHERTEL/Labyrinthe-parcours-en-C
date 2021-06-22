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

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    drawLab(window, renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);

    quitSDL(true, "SDL END", window, renderer);

    return 0;
}

void drawLab(SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_Rect positionLab = {0},
             window_dimensions = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    positionLab.h = window_dimensions.h * 0.9;
    positionLab.w = window_dimensions.w * 0.9;
    positionLab.x = (window_dimensions.w - positionLab.w) / 2 ;
    positionLab.y = (window_dimensions.h - positionLab.h) / 2 ;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &positionLab);

}
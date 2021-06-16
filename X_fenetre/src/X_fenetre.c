#include "X_fenetre.h"

int taileEcran(int *h, int* w)
{
    SDL_DisplayMode current;
    int code = 0;

    if(SDL_GetCurrentDisplayMode(0, &current) != 0)
   {
       code = 1;
   }
   else
   {
        *h = current.h;
        *w = current.w;
   }
    return code;
}

void deplacerFenetres(SDL_Window  * window_1,SDL_Window * window_2,SDL_Window* window_4, SDL_Window* window_5, int pas)
{
    int window_x,
         window_y;
    SDL_GetWindowPosition(window_1, &window_x, &window_y);
    SDL_SetWindowPosition(window_1, window_x, window_y + 2*pas);
    SDL_GetWindowPosition(window_2, &window_x, &window_y);
    SDL_SetWindowPosition(window_2, window_x, window_y + pas);
    SDL_GetWindowPosition(window_4, &window_x, &window_y);
    SDL_SetWindowPosition(window_4, window_x, window_y - pas);
    SDL_GetWindowPosition(window_5, &window_x, &window_y);
    SDL_SetWindowPosition(window_5, window_x, window_y - 2*pas);
}

int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window  * window_1,
                             * window_2,
                             * window_3,
                             * window_4,
                             * window_5 ;
    int                        window_h, 
                                window_w,
                                height,
                                weight,
                                i, 
                                x,
                                y;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    //Recuperation de la taille de l'ecran
    if(taileEcran(&window_h, &window_w) != 0)
    {
        SDL_Log("Error : SDL Display Mode - %s\n", SDL_GetError()); 
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    weight = window_w / 5 ;
    height = window_h / 5;

    //Creation de toutes les fenetres
    window_1 = SDL_CreateWindow("Fenêtre 1", 0, window_h/2 - height/2, weight, height, SDL_WINDOW_RESIZABLE);
    if (window_1 == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    window_2 = SDL_CreateWindow("Fenêtre 2", weight, window_h/2 - height/2, weight, height, SDL_WINDOW_RESIZABLE);
    if (window_1 == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    window_3 = SDL_CreateWindow("Fenêtre 3", 2*weight, window_h/2 - height/2, weight, height, SDL_WINDOW_RESIZABLE);
    if (window_1 == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    window_4 = SDL_CreateWindow("Fenêtre 4", 3*weight, window_h/2 - height/2, weight, height, SDL_WINDOW_RESIZABLE);
    if (window_1 == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    window_5 = SDL_CreateWindow("Fenêtre 5", 4*weight, window_h/2 - height/2, weight, height, SDL_WINDOW_RESIZABLE);
    if (window_1 == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    //On descend
    for(i=0; i<50; i++)
    {
        SDL_Delay(10);
        deplacerFenetres(window_1, window_2, window_4, window_5, 5);
    }
    //On remonte
    for(i=0; i<100; i++)
    {
        SDL_Delay(10);
        deplacerFenetres(window_1, window_2, window_4, window_5, -5);
    }

    //Destruction des fenetres inutiles
    SDL_DestroyWindow(window_1);
    SDL_DestroyWindow(window_2);
    SDL_DestroyWindow(window_4);
    SDL_DestroyWindow(window_5);

    //On agrandi celle du milieu
    for(i=0; i<50; i++)
    {
        SDL_Delay(10);
        SDL_GetWindowSize(window_3, &window_w, &window_h);
        SDL_SetWindowSize(window_3, window_w+10, window_h+10);
        SDL_GetWindowPosition(window_3, &x, &y);
        SDL_SetWindowPosition(window_3, x -5, y - 5);
    }

    SDL_Delay(500);

    //Destruction de la derniere fenetre
    SDL_DestroyWindow(window_3);

    SDL_Quit();
    return 0;
}
#include "labyrintheVue.h"

void dimensionsLab(SDL_Rect *positionLab, SDL_Rect tile, int n, int m)
{
    positionLab->x = (positionLab->w - tile.w * m) / 2;
    positionLab->y = (positionLab->h - tile.h * n) / 2;
}

void dimensionTile(SDL_Rect *tile, SDL_Rect positionLab, int n, int m)
{
    int a,
        b;

    a = positionLab.w / m;
    b = positionLab.h / n;
    tile->w = tile->h = a <= b ? a : b;
}

void dimensionPerso(SDL_Rect *dest, SDL_Rect tile)
{
    dest->w = tile.w * 0.8;
    dest->h = tile.h * 0.8;
}

void drawperso(SDL_Renderer *renderer, SDL_Texture *perso, SDL_Rect dest)
{
    SDL_Rect source = {423, 44, 35, 43};

    SDL_RenderCopy(renderer, perso, &source, &dest);
}

void drawLab(SDL_Renderer *renderer, int **grid, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, bool_t *marques)
{
    SDL_Rect wallNS = {0},              // Nord et Sud destination
        wallEO = {0},                   // Est et Ouest destination
        wallSourceNS = {0, 64, 64, 12}, // Nord et Sud source
        wallSourceEO = {0, 0, 12, 64},  // Est et Ouest source
        groundSource = {96, 126, 64, 64},
             stoneSource = {35, 0, 35, 30};
    int pos,
        i = 0,
        j = 0;

    wallEO.w = tile.w * 0.1;
    wallEO.h = tile.h + (tile.h * 0.1);

    wallNS.w = tile.w + (tile.w * 0.1);
    wallNS.h = tile.h * 0.1;

    positionLab.x = (positionLab.w - tile.w * m) / 2;
    positionLab.y = (positionLab.h - tile.h * n) / 2;

    // Sols
    for (i = 0; i < n; i++)
    {
        tile.y = positionLab.y + tile.h * i;
        for (j = 0; j < m; j++)
        {
            tile.x = positionLab.x + tile.w * j;
            SDL_RenderCopy(renderer, texture, &groundSource, &tile);
            if (marques)
            {
                pos = i * n + j;
                if (marques[pos])
                {
                    SDL_RenderFillRect(renderer, &tile);
                    SDL_RenderCopy(renderer, texture, &stoneSource, &tile);
                }
            }
        }
    }

    // Murs
    for (i = 0; i < n; i++)
    {
        tile.y = positionLab.y + tile.h * i;
        for (j = 0; j < m; j++)
        {
            tile.x = positionLab.x + tile.w * j;

            if (grid[i][j] & SUD)
            {
                wallNS.x = tile.x - (tile.w * 0.1) / 2;
                wallNS.y = tile.y + tile.h - (tile.h * 0.1) / 2;
                SDL_RenderFillRect(renderer, &wallNS);
                SDL_RenderCopy(renderer, texture, &wallSourceNS, &wallNS);
            }
            if (grid[i][j] & EST)
            {
                wallEO.x = tile.x + tile.w - (tile.w * 0.1) / 2;
                wallEO.y = tile.y - (tile.h * 0.1) / 2;
                SDL_RenderFillRect(renderer, &wallEO);
                SDL_RenderCopy(renderer, texture, &wallSourceEO, &wallEO);
            }
        }
    }

    // Grand mur de gauche
    tile.x = positionLab.x;
    wallEO.x = tile.x - (tile.w * 0.1) / 2;
    for (i = 0; i < n; i++)
    {
        tile.y = positionLab.y + tile.h * i;
        wallEO.y = tile.y - (tile.h * 0.1) / 2;
        SDL_RenderFillRect(renderer, &wallEO);
        SDL_RenderCopy(renderer, texture, &wallSourceEO, &wallEO);
    }

    // Grand mur du haut
    tile.y = positionLab.y;
    wallNS.y = tile.y - (tile.h * 0.1) / 2;
    for (i = 0; i < m; i++)
    {
        tile.x = positionLab.x + tile.w * i;
        wallNS.x = tile.x - (tile.w * 0.1) / 2;
        SDL_RenderFillRect(renderer, &wallNS);
        SDL_RenderCopy(renderer, texture, &wallSourceNS, &wallNS);
    }
}

void drawStone(SDL_Renderer *renderer, int indiceNoeud, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture)
{
    int i, j;
    SDL_Rect source = {35, 0, 35, 30};

    i = indiceNoeud / n;
    j = indiceNoeud - i * m;

    tile.y = positionLab.y + tile.h * i + tile.h * 0.1;
    tile.x = positionLab.x + tile.w * j + tile.w * 0.1;
    tile.w = tile.h = tile.w * 0.8;

    SDL_RenderFillRect(renderer, &tile);
    SDL_RenderCopy(renderer, texture, &source, &tile);
}

void drawAll(bool_t *marques, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    drawLab(renderer, grille, n, m, tile, positionLab, texture, marques);
    if (perso)
    {
        drawperso(renderer, perso, destPerso);
    }
}

bool_t drawText(char *text, SDL_Rect dest, TTF_Font *font, SDL_Renderer *renderer)
{
    SDL_Color color = {0};
    SDL_Rect source = {0};
    SDL_Texture *texture;
    SDL_Surface *surface;

    color.a = 255;

    surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL)
    {
        fputs("erreur ouverture de la police\n", stderr);
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        fputs("erreur transformation de la surface de la police en texture\n", stderr);
        SDL_FreeSurface(surface);
        return false;
    }
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
    SDL_RenderCopy(renderer, texture, &source, &dest);
    SDL_DestroyTexture(texture);
    return true;
}

void dimensionButtons(SDL_Rect *dijkstra, SDL_Rect *a_etoile, SDL_Rect *profondeur, SDL_Rect *quit, SDL_Rect positionLab)
{
    dijkstra->w = positionLab.w * 0.3;
    dijkstra->h = positionLab.h * 0.1;
    dijkstra->x = (positionLab.w - dijkstra->w) / 2; 
    dijkstra->y = positionLab.h * 0.2 + dijkstra->h / 2;
    a_etoile->w = positionLab.w * 0.1;
    a_etoile->h = positionLab.h * 0.1;
    a_etoile->x = (positionLab.w - a_etoile->w) / 2; 
    a_etoile->y = dijkstra->y + dijkstra->h + a_etoile->h / 2;
    profondeur->w = positionLab.w * 0.3;
    profondeur->h = positionLab.h * 0.1;
    profondeur->x = (positionLab.w - profondeur->w) / 2; 
    profondeur->y = a_etoile->y + a_etoile->h + profondeur->h / 2;
    quit->w = positionLab.w * 0.3;
    quit->h = positionLab.h * 0.1;
    quit->x = (positionLab.w - quit->w) / 2; 
    quit->y = positionLab.h - quit->h * 1.5;
}

void drawMenu(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect positionLab, SDL_Rect dijkstra, SDL_Rect a_etoile, SDL_Rect profondeur, SDL_Rect quit)
{
    SDL_Rect titre = {0};

    titre.w = positionLab.w * 0.5;
    titre.h = positionLab.h * 0.2;
    titre.x = (positionLab.w - titre.w) / 2; 
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // fond

    SDL_SetRenderDrawColor(renderer, 140, 120, 120, 255);
    SDL_RenderFillRect(renderer, &dijkstra);
    SDL_RenderFillRect(renderer, &a_etoile);
    SDL_RenderFillRect(renderer, &profondeur);

    SDL_SetRenderDrawColor(renderer, 185, 25, 10, 255);
    SDL_RenderFillRect(renderer, &quit);

    drawText("Parcours !", titre, font, renderer);
    drawText("Dijkstra", dijkstra, font, renderer);
    drawText("A*", a_etoile, font, renderer);
    drawText("Profondeur", profondeur, font, renderer);
    drawText("Quitter", quit, font, renderer);
}

void menuLoop(SDL_Renderer * renderer, TTF_Font *font, SDL_Texture *texture, SDL_Texture *perso)
{
    SDL_Rect positionLab = {0},
             tile = {0},
             dijkstra = {0},
             a_etoile = {0},
             profondeur = {0},
             quit = {0},
             mouse = {0};
    SDL_bool program_on = SDL_TRUE;

    dimensionButtons(&dijkstra, &a_etoile, &profondeur, &quit, positionLab);

    while(program_on)
    {
        SDL_Event event;                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) 
        {                               // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) 
            {
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        // Calcul des dimensions quand la fenetre change de taille
                        dimensionButtons(&dijkstra, &a_etoile, &profondeur, &quit, positionLab);
                    }
                    break;
                case SDL_QUIT:                         
                    program_on = SDL_FALSE;                   
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) 
                    {             
                        case SDLK_ESCAPE:                           // 'ESCAPE'  
                        case SDLK_q:                                // 'q'
                            program_on = SDL_FALSE;
                            break;
                        default:                      
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:     
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    //Calcul des coordonnees par rapport a l'emplacement du labyrinthe
                    
                    if (SDL_BUTTON(SDL_BUTTON_LEFT) ) 
                    {                       

                    } 
                    break;
                default:                                            
                    break;
            }
        } 
        drawMenu(renderer, font, positionLab, dijkstra, a_etoile, profondeur, quit);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(50);
    }
}

/*void gameloop()
{
    SDL_bool  program_on = SDL_TRUE,                          // Booleen pour dire que le programme doit continuer
              paused = SDL_FALSE;                             // Booleen pour dire que le programme est en pause
    

    // Initialisation des coordonnees

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
                        // Calcul des dimensions quand la fenetre change de taille
                        
                    }
                    break;
                case SDL_QUIT:                         
                    program_on = 0;                   
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) 
                    {             
                        case SDLK_LEFT:
                            paddleSpeed = -2;
                        	break;
                        case SDLK_RIGHT:
                            paddleSpeed = 2;
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
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) 
                    {             
                        case SDLK_LEFT:         
                            paddleSpeed = 0;
                        	break;
                        case SDLK_RIGHT:
                            paddleSpeed = 0;
                        	break;
                        default :
                            break;
                    }
                default:                                            
                    break;
            }
        } 

        if(gameIsOver)
        {

        }

        if (!paused) 
        {      
                                
        }
        SDL_Delay(50);                                  
    }
    SDL_DestroyTexture(texture);
}*/

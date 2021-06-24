#include "main.h"

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
    SDL_Texture *texture,
        *perso;
    SDL_Rect positionLab = {0},
             tile = {0},
             dijkstra = {0},
             a_etoile = {0},
             profondeur = {0},
             quit = {0};
    TTF_Font *font;

    (void)argc;
    (void)argv;

    // // INITIALISATION
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

    if (TTF_Init() != 0)
    {
        quitSDL(false, "ERROR TTF INIT", window, renderer);
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont("../fonts/font.ttf", 500);
    if (font == NULL)
    {
        quitSDL(false, " error font\n", window, renderer);
        exit(EXIT_FAILURE);
    }

    texture = loadTextureFromImage("../images/texture.png", renderer);
    if (texture == NULL)
    {
        quitSDL(0, " error texture\n", window, renderer);
        exit(EXIT_FAILURE);
    }

    perso = loadTextureFromImage("../images/persos.png", renderer);
    if (perso == NULL)
    {
        quitSDL(0, " error texture\n", window, renderer);
        exit(EXIT_FAILURE);
    }

    // // TRAITEMENT

    SDL_Rect destPerso = {0};
    int n = 8, tailleLabyrintheCouvrant, m;
    couples_graphe_t graph;
    int **grille;
    liste_t chemin;
    maillon_t *cour;

    m = n;
    genererGrapheLabyrinthe(&graph, n);
    graph.aretes = kruskal_non_arbo(graph, &tailleLabyrintheCouvrant, 0.9);
    graph.nbAretes = tailleLabyrintheCouvrant;
    grille = arbreCouvrantToMatrice(graph.aretes, tailleLabyrintheCouvrant, n);

    SDL_GetWindowSize(window, &positionLab.w, &positionLab.h);
    dimensionTile(&tile, positionLab, n, m);
    dimensionsLab(&positionLab, tile, n, m);
    dimensionPerso(&destPerso, tile);
    dimensionButtons(&dijkstra, &a_etoile, &profondeur, &quit, positionLab);
    
    int deb, fin;
    deb = randomNoeud(graph, -1);
    fin = randomNoeud(graph, deb);

    parcoursEnProfondeur(graph, deb, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso, 50);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    drawLab(renderer, grille, n, m, tile, positionLab, texture, NULL);
    /*
    if(dijkstra(graph, deb, fin, &chemin, n * m)) {
        cour = chemin;
        while(cour != NULL) {
            drawStone(renderer, cour->v, n, m, tile, positionLab, texture);
            cour = cour->suiv;
        }
        libererListe(chemin);
    }
    else {
        fprintf(stderr, "erreur dijkstra\n");
	    printAretes(graph);
    }
    SDL_RenderPresent(renderer);
    */
    //SDL_RenderClear(renderer);
    //drawMenu(renderer, font, positionLab, dijkstra, a_etoile, profondeur, quit);
    //SDL_RenderPresent(renderer);
    //SDL_Delay(1000);

    menuLoop(window, renderer, font, texture, perso);

    free(graph.aretes);
    for (int i = 0; i < m; ++i)
    {
        free(grille[i]);
    }
    free(grille);
    quitSDL(true, "SDL END", window, renderer);

    return 0;
}

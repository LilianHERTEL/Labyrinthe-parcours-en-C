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
             tile = {0};

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

    SDL_Rect dest = {0};
    int n = 5, tailleLabyrintheCouvrant, m;
    couples_graphe_t graph;
    int** grille;
    liste_t chemin;
    maillon_t *cour;

    m=n;
    genererGrapheLabyrinthe(&graph, n);
    graph.aretes = kruskal_non_arbo(graph, &tailleLabyrintheCouvrant, 0.9);
    graph.nbAretes = tailleLabyrintheCouvrant;
    grille = arbreCouvrantToMatrice(graph.aretes, tailleLabyrintheCouvrant, n);

    SDL_GetWindowSize(window, &positionLab.w, &positionLab.h);
    dimensionTile(&tile, positionLab, n, m);
    dimensionPerso(&dest, tile);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    drawLab(renderer, grille, n, m, tile, positionLab, texture);

    int deb, fin;
    deb = randomNoeud(graph, -1);
    fin = randomNoeud(graph, deb);

    drawOtherTile(renderer, deb, n, m, tile, positionLab, texture);
    drawOtherTile(renderer, fin, n, m, tile, positionLab, texture);

    drawperso(renderer, perso, dest);

    if(dijkstra(graph, deb, fin, &chemin, n * m)) {
        cour = chemin;
        while(cour != NULL) {
            drawOtherTile(renderer, cour->v, n, m, tile, positionLab, texture);
        }
        libererListe(chemin);
    }
    else {
        fprintf(stderr, "erreur dijkstra\n");
	printAretes(graph);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    quitSDL(true, "SDL END", window, renderer);

    return 0;
}

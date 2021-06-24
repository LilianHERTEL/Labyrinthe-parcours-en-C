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

    SDL_Rect destPerso = {0};
    int n = 15, tailleLabyrintheCouvrant, m;
    couples_graphe_t graph;
    int** grille;
    liste_t chemin;
    maillon_t *cour;

    m=n;
    genererGrapheLabyrinthe(&graph, n);
    graph.aretes = kruskal_non_arbo(graph, &tailleLabyrintheCouvrant, 0.9);
    graph.nbAretes = tailleLabyrintheCouvrant;
    grille = arbreCouvrantToMatrice(graph.aretes, tailleLabyrintheCouvrant, n);

    /*displayGrid(grille, n, m);
    int nbVois;
    int* voisins = trouverVoisins(graph, 7, &nbVois);
    printf("%d voisins\n", nbVois);
    for (int i = 0; i < nbVois; i++)
    {
        printf("VOISIN : %d\n", voisins[i]);
    }*/
    

    SDL_GetWindowSize(window, &positionLab.w, &positionLab.h);
    dimensionTile(&tile, positionLab, n, m);
    dimensionsLab(&positionLab, tile, n, m);
    dimensionPerso(&destPerso, tile);

    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    //drawLab(renderer, grille, n, m, tile, positionLab, texture);

    int deb, fin;
    deb = randomNoeud(graph, -1);
    fin = randomNoeud(graph, deb);

    //drawOtherTile(renderer, deb, n, m, tile, positionLab, texture);
    //drawOtherTile(renderer, fin, n, m, tile, positionLab, texture);

    //drawperso(renderer, perso, destPerso);

    /*bool_t * marques;
    int s= deb;
    marques = (bool_t *)malloc(sizeof(bool_t) * 5);
    for(int z = 0; z<5; z++)
    {
        marques[z] = true;
    }

    SDL_Delay(500);
    for(int z = 0; z < 5; z++)
    {
        deb = randomNoeud(graph, deb);
        s = deb;
        drawLab(renderer, grille, n, m, tile, positionLab, texture);
        drawChemin(renderer, n, m, tile, positionLab, texture, marques, graph.nbNoeuds);
        int l = s/n;
        int c = s - l*n;
        destPerso.x = positionLab.x + tile.w * c + tile.w * 0.1;
        destPerso.y = positionLab.y + tile.h * l + tile.h * 0.1;
        drawperso(renderer, perso, destPerso);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000);
    }*/

    parcoursEnProfondeur(graph, deb, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso);

/*
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
    }*/

    //SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    quitSDL(true, "SDL END", window, renderer);

    return 0;
}

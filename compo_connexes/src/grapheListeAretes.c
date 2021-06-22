#include "grapheListeAretes.h"

void genererGraphe(couples_graphe_t* graphe, int nbNoeuds) {
    int i, nbAretes = 0;
    graphe->nbNoeuds = nbNoeuds;
    srand(time(NULL));
    nbAretes = rand()%nbNoeuds;
    graphe->aretes = (arete_t*)malloc(nbNoeuds * sizeof(arete_t));
    if (graphe->aretes != NULL)
    {
        graphe->nbAretes = nbAretes;
        //printf("nb = %d\n", graphe->nbAretes);
        for (i = 0; i < nbAretes; i++)
        {
            graphe->aretes[i].noeudDeb = rand()%nbNoeuds;
            printf("deb = %d\n", graphe->aretes[i].noeudDeb);
            graphe->aretes[i].noeudFin = rand()%(nbNoeuds-graphe->aretes[i].noeudDeb) + graphe->aretes[i].noeudDeb;
            printf("fin = %d\n", graphe->aretes[i].noeudFin);
        }
    }
    else
    {
        puts("Error: memory allocation failed\n");
    }
}

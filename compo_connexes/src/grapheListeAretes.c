#include "grapheListeAretes.h"

void genererGraphe(couples_graphe_t* graphe, int nbNoeuds) {
    int i, nbAretes = 0, deb, fin;
    graphe->nbNoeuds = nbNoeuds;
    srand(time(NULL));
    nbAretes = rand()%(nbNoeuds*2) + nbNoeuds/2;
    graphe->aretes = (arete_t*)malloc(nbAretes * sizeof(arete_t));
    if (graphe->aretes != NULL)
    {
        graphe->nbAretes = 0;
        for (i = 0; i < nbAretes; i++)
        {
            do {
                deb = rand()%nbNoeuds;
                fin = rand()%(nbNoeuds-deb) + deb;
                graphe->aretes[i].noeudDeb = deb;
                graphe->aretes[i].noeudFin = fin;
            }
            while (aretePasValide(graphe, deb, fin));
            
            (graphe->nbAretes)++;
        }
        graphe->nbAretes = nbAretes;
    }
    else
    {
        puts("Error: memory allocation failed\n");
    }
}

bool_t aretePasValide(couples_graphe_t* graphe, int deb, int fin) {
    bool_t status = false;
    int i;
    if (deb == fin) status = true;
    for (i = 0; i < graphe->nbAretes; i++)
    {
        if (graphe->aretes[i].noeudDeb == deb && graphe->aretes[i].noeudFin == fin) status = true;
    }
    return status;
}
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
            graphe->aretes[i].poids = rand() % 30; 
            graphe->aretes[i].noeudDeb = rand()%nbNoeuds;
            //printf("deb = %d\n", graphe->aretes[i].noeudDeb);
            graphe->aretes[i].noeudFin = rand()%(nbNoeuds-graphe->aretes[i].noeudDeb) + graphe->aretes[i].noeudDeb;
            //printf("fin = %d\n", graphe->aretes[i].noeudFin);
        }
    }
    else
    {
        puts("Error: memory allocation failed\n");
    }
}

void ordonnerAretesCroissant(couples_graphe_t * graph)
{
    qsort(graph->aretes, graph->nbAretes, sizeof(arete_t), comparArete);
}

int comparArete(const void * arete_1, const void * arete_2)
{
    const arete_t *ar1 = arete_1;
    const arete_t *ar2 = arete_2;
    if(ar1->poids > ar2->poids)
    {
        return 1;
    }
    else if(ar1->poids == ar2->poids)
    {
        return 0;
    }
    return -1;
}
#include "grapheListeAretes.h"

void genererGraphe(couples_graphe_t *graphe, int nbNoeuds)
{
    int i, nbAretes = 0, deb, fin;
    graphe->nbNoeuds = nbNoeuds;
    srand(time(NULL));
    nbAretes = rand() % (nbNoeuds * 2) + nbNoeuds / 2;
    graphe->aretes = (arete_t *)malloc(nbAretes * sizeof(arete_t));
    if (graphe->aretes != NULL)
    {
        graphe->nbAretes = 0;
        for (i = 0; i < nbAretes; i++)
        {
            graphe->aretes[i].poids = 1;
            do
            {
                deb = rand() % nbNoeuds;
                fin = rand() % (nbNoeuds - deb) + deb;
                graphe->aretes[i].noeudDeb = deb;
                graphe->aretes[i].noeudFin = fin;
            } while (aretePasValide(graphe, deb, fin));

            (graphe->nbAretes)++;
        }
        graphe->nbAretes = nbAretes;
    }
    else
    {
        puts("Error: memory allocation failed\n");
    }
}

void printAretes(couples_graphe_t graph) {
    int i;
    puts("Affichage des arêtes : \n");
    for (i = 0; i < graph.nbAretes; ++i)
    {
        printf("%d ---%d--> %d\n", graph.aretes[i].noeudDeb, graph.aretes[i].poids, graph.aretes[i].noeudFin);
    }
}

void ordonnerAretesCroissant(couples_graphe_t *graph)
{
    qsort(graph->aretes, graph->nbAretes, sizeof(arete_t), comparArete);
}

void permute(arete_t aretes[], int i, int j)
{
    arete_t tmp = aretes[i];
    aretes[i] = aretes[j];
    aretes[j] = tmp;
}

void fisherYate(couples_graphe_t *graph)
{
    int i, j;
    srand(time(NULL));
    for (i = graph->nbAretes - 1; i > 1; i--)
    {
        j = rand() % i + 1;
        permute(graph->aretes, i, j);
    }
}

int comparArete(const void *arete_1, const void *arete_2)
{
    const arete_t *ar1 = arete_1;
    const arete_t *ar2 = arete_2;
    if (ar1->poids > ar2->poids)
    {
        return 1;
    }
    else if (ar1->poids == ar2->poids)
    {
        return 0;
    }
    return -1;
}

bool_t aretePasValide(couples_graphe_t *graphe, int deb, int fin)
{
    bool_t status = false;
    int i;
    if (deb == fin)
        status = true;
    for (i = 0; i < graphe->nbAretes; i++)
    {
        if (graphe->aretes[i].noeudDeb == deb && graphe->aretes[i].noeudFin == fin)
            status = true;
    }
    return status;
}
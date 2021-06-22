#include <stdio.h>
#include "compoConnexes2.h"

void genererGraphe(graphe_t graphe, int nbNoeuds) {
    int i, nbAretes = 0;
    graphe.nbNoeuds = nbNoeuds;
    srand(time(NULL));
    nbAretes = rand()%(nbNoeuds/2);
    graphe.aretes = (arete_t*)malloc(nbNoeuds * sizeof(arete_t));
    if (graphe.aretes != NULL)
    {
        for (i = 0; i < nbAretes; i++)
        {
            graphe.aretes[i].noeudDeb = rand()%nbNoeuds;
            printf("deb = %d\n", graphe.aretes[i].noeudDeb);
            graphe.aretes[i].noeudFin = rand()%(nbNoeuds-graphe.aretes[i].noeudDeb) + graphe.aretes[i].noeudDeb;
            printf("fin = %d\n", graphe.aretes[i].noeudFin);
        }
    }
    else
    {
        puts("Error: memory allocation failed\n");
    }
}

int main(void)
{
	int n = 10;
	graphe_t graph;
	
	genererGraphe(graph, n);

	return 0;
}
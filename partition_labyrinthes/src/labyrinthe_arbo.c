#include "labyrinthe_arbo.h"
/*
void genererLabyrinthe(laby, nblignes) {
	int sizeligne = 20;

	graphe = malloc(nbligne * sizeligne);
	
	return laby;
}
*/

void genererGrapheLabyrinthe(couples_graphe_t *graphe, int size)
{
    int i, nbAretes = 0, deb, fin, j = 2;
    graphe->nbNoeuds = size*size;
    graphe->nbAretes = graphe->nbNoeuds* 2 - (size * 2) ;
    graphe->aretes = (arete_t *)malloc(graphe->nbAretes * sizeof(arete_t));
    if (graphe->aretes != NULL && size > 2)
    {
        graphe->aretes[0].noeudDeb = 0;
        graphe->aretes[0].noeudFin = 1;
        graphe->aretes[1].noeudDeb = 0;
        graphe->aretes[1].noeudFin = size;
        for (i = 1; i < graphe->nbNoeuds - 1; i++)
        {
            if (((i+1)%size != 0) && (i < (size-1)*size))
            {
                graphe->aretes[j].noeudDeb = i;
                graphe->aretes[j].noeudFin = i + 1;
                graphe->aretes[j].poids = 1;
                j++;

                graphe->aretes[j].noeudDeb = i;
                graphe->aretes[j].noeudFin = i + size;
                graphe->aretes[j].poids = 1;
                j++;
            }
            else
            {
                if (i%size == size-1 && (i < (size-1)*size))
                {
                    graphe->aretes[j].noeudDeb = i;
                    graphe->aretes[j].noeudFin = i + size;
                    graphe->aretes[j].poids = 1;
                    j++;
                }
                else if (i >= (size-1)*size && i < size*size-1)
                {
                    graphe->aretes[j].noeudDeb = i;
                    graphe->aretes[j].noeudFin = i + 1;
                    graphe->aretes[j].poids = 1;
                    j++;
                }
                
            }
        }
    }
    else
    {
        puts("Error: memory allocation failed\n");
    }
}
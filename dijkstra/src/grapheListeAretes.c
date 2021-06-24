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

void printAretes(couples_graphe_t graph)
{
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

void exchange(arete_t aretes[], int i, int j)
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
        exchange(graph->aretes, i, j);
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

void genererGrapheLabyrinthe(couples_graphe_t *graphe, int size)
{
    int i, j = 2;
    graphe->nbNoeuds = size * size;
    graphe->nbAretes = graphe->nbNoeuds * 2 - (size * 2);
    graphe->aretes = (arete_t *)malloc(graphe->nbAretes * sizeof(arete_t));
    if (graphe->aretes != NULL && size > 2)
    {
        graphe->aretes[0].noeudDeb = 0;
        graphe->aretes[0].noeudFin = 1;
        graphe->aretes[0].poids = 1;
        graphe->aretes[1].noeudDeb = 0;
        graphe->aretes[1].noeudFin = size;
        graphe->aretes[1].poids = 1;
        for (i = 1; i < graphe->nbNoeuds - 1; i++)
        {
            if (((i + 1) % size != 0) && (i < (size - 1) * size))
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
                if (i % size == size - 1 && (i < (size - 1) * size))
                {
                    graphe->aretes[j].noeudDeb = i;
                    graphe->aretes[j].noeudFin = i + size;
                    graphe->aretes[j].poids = 1;
                    j++;
                }
                else if (i >= (size - 1) * size && i < size * size - 1)
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

int **arbreCouvrantToMatrice(arete_t *arbre, int nbAretes, int taille)
{
    int **matrice = NULL;
    int deb, fin, l, c;
    matrice = allocGrid(taille, taille);
    if (matrice != NULL)
    {
        for (int i = 0; i < nbAretes; i++)
        {
            deb = arbre[i].noeudDeb;
            fin = arbre[i].noeudFin;
            l = deb / taille;
            c = deb - l * taille;

            if (fin == deb + 1)
            {
                matrice[l][c] -= 4;
            }
            if (fin == deb + taille)
            {
                matrice[l][c] -= 2;
            }
        }
    }
    return matrice;
}

int randomNoeud(couples_graphe_t graph, int noeudDeb)
{
    int random;
    srand(time(NULL));
    random = rand() % (graph.nbNoeuds);
    while(random == noeudDeb)
    {
        random = rand() % (graph.nbNoeuds);
    }
    return random;
}

int* trouverVoisins(couples_graphe_t graphe, int noeud, int* nbVoisins) {
    int i;
    *nbVoisins = 0;
    int* voisins = (int*) malloc(4*sizeof(int));
    if (voisins != NULL)
    {
        while (i < graphe.nbAretes && *nbVoisins < 4)
        {
            if (graphe.aretes[i].noeudDeb == noeud)
            {
                voisins[*nbVoisins] = graphe.aretes[i].noeudFin;
                (*nbVoisins)++;
            }
            else if (graphe.aretes[i].noeudFin == noeud)
            {
                voisins[*nbVoisins] = graphe.aretes[i].noeudDeb;
                (*nbVoisins)++;
            }
            i++;
        }
    }
    else
    {
        printf("Error: malloc failed\n");
    }
    return voisins;
}

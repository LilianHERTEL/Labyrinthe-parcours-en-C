#include <stdio.h>
#include <stdlib.h>
#include "grapheListeAretes.h"

void genererGrapheLabyrinthe(couples_graphe_t *graphe, int size);
int** arbreCouvrantToMatrice(arete_t* arbre, int nbAretes, int taille);
#pragma once

#include "partition.h"
#include <time.h>

typedef int *graphe_t;

void genererMatriceAdjacence(graphe_t graphe, int n);
void afficherMatriceAdjacence(int* matrix, int n);
void afficherGraphe(graphe_t graphe);
element_t** noeudsCompoConnexes(graphe_t graphe);
void afficherSousGraphe(graphe_t graphe, element_t* sgraphe);

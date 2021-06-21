#pragma once

#include "partition.h"
#include <time.h>

typedef int *graphe_t;

graphe_t createAdjencyMatrix(int n);
void afficherMatriceAdjacence(graphe_t matrix, int n);
void afficherGraphe(graphe_t graphe);
element_t** noeudsCompoConnexes(graphe_t graphe, int n);
void afficherSousGraphe(graphe_t graphe, element_t* sgraphe);
partition_t grapheToPartition(graphe_t graphe, int n);

#pragma once

#include "partition.h"
#include <time.h>

typedef int *graphe_t;

graphe_t createAdjencyMatrix(int n);
void afficherMatriceAdjacence(graphe_t matrix, int n);
element_t** noeudsCompoConnexes(graphe_t graphe, int n, int * noeudsI);
partition_t grapheToPartition(graphe_t graphe, int n);
void afficherNoeudsCompoConnexes(element_t ** noeuds, int n_noeuds, int n);
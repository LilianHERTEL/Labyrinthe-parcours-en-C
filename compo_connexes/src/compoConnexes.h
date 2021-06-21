#pragma once

#include "partition.h"

typedef int **graphe_t;

void genererMatriceAdjacence(graphe_t *graphe);
void afficherGraphe(graphe_t graphe);
element_t** noeudsCompoConnexes(graphe_t graphe);
void afficherSousGraphe(graphe_t graphe, element_t* sgraphe);

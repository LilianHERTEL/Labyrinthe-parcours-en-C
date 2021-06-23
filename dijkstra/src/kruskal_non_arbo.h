#pragma once

#include <stdlib.h>
#include <time.h>
#include "partition.h"
#include "grapheListeAretes.h"

arete_t * kruskal_non_arbo(couples_graphe_t graph, int * tailleListe, float densite);

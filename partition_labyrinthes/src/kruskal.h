#pragma once

#include <stdio.h>
#include "kruskal.h"
#include <stdlib.h>
#include "grapheListeAretes.h"
#include "partition.h"

arete_t * arbreCouvrantPoidsMin(couples_graphe_t graph, int * tailleListe);

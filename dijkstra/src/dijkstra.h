#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_heap.h"
#include "grapheListeAretes.h"
#include "bool.h"

bool_t dijkstra(couples_graphe_t graphe, int source, int cible, int *chemin, int n);

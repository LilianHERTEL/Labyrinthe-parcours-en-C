#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "binary_heap_t"
#include "bool.h"

bool dijkstra(graphe_t graphe, int source, int cible, int *chemin, int n);

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_heap.h"
#include "grapheListeAretes.h"
#include "bool.h"
#include "liste_chainee.h"

bool_t dijkstra(couples_graphe_t graphe, int source, int cible, liste_t *chemin, int n);

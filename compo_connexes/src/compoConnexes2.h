#pragma once

#include "partition.h"
#include <time.h>

typedef struct
{
    int noeudDeb;
    int noeudFin;
} arete_t;

typedef struct
{
    int noeuds;
    arete_t* aretes;
} graphe_t;

void genererGraphe(graphe_t graphe, int n);
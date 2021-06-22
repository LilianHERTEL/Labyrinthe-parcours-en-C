#pragma once

#include <stdlib.h>
#include <time.h>
#include "partition.h"
#include "bool.h"

typedef struct
{
    int noeudDeb;
    int noeudFin;
} arete_t;

typedef struct
{
    int nbNoeuds;
    int nbAretes;
    arete_t* aretes;
} couples_graphe_t;

void genererGraphe(couples_graphe_t* graphe, int n);
bool_t aretePasValide(couples_graphe_t* graphe, int deb, int fin);
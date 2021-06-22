#pragma once

#include <stdlib.h>
#include <time.h>
#include "partition.h"

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
void afficherGraphe2(couples_graphe_t graphe); // affiche dans la console (pour tests)
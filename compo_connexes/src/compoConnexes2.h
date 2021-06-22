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
    int nbNoeuds;
    arete_t* aretes;
} graphe_t;

void genererGraphe(graphe_t graphe, int n);
void afficherGraphe(graphe_t graphe); // affiche dans la console (pour tests)
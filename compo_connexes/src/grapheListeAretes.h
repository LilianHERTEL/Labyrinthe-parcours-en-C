#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partition.h"
#include "bool.h"

typedef struct
{
    int poids;
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

void ordonnerAretesCroissant(couples_graphe_t * graph);
int comparArete(const void * arete_1, const void * arete_2);
bool_t aretePasValide(couples_graphe_t* graphe, int deb, int fin);

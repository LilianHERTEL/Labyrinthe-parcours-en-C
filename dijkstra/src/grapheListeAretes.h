#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bool.h"
#include "matrice.h"

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
void supprimerGraphe(couples_graphe_t graphe);

void printAretes(couples_graphe_t graph);
void exchange(arete_t *aretes, int i, int j);
void fisherYate(couples_graphe_t *graph);

void genererGrapheLabyrinthe(couples_graphe_t *graphe, int size);
int **arbreCouvrantToMatrice(arete_t *arbre, int nbAretes, int taille);
int randomNoeud(couples_graphe_t graph, int noeudDeb);
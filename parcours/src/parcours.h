#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "binary_heap.h"
#include "grapheListeAretes.h"
#include "bool.h"
#include "liste_chainee.h"
#include "labyrintheVue.h"

bool_t dijkstra(couples_graphe_t graphe, int source, int cible, liste_t *chemin, int n);

bool_t astar(int **graphe, int source, int cible, liste_t *chemin, int n, int m);

void checkVoisinAstar(int numvoisin, node_t cour, int *prec, bool_t *traite, binary_heap_t *tas, int cible, int n);

int manhattan(int courx, int coury, int ciblex, int cibley);

void checkVoisin(int voisinCourant, node_t cour, arete_t areteVoisin, int *prec, bool_t *traite, binary_heap_t *tas);

void parcoursEnProfondeur(couples_graphe_t graph, int debut, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso);

void initialiserMarque(bool_t *marques, int n);

void explorer(couples_graphe_t graph, int s, bool_t *marques, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso);

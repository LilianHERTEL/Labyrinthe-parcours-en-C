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

/**
 * @brief Applique l'algorithme de dijkstra sur un graphe
 * 
 * @param graphe Le graphe 
 * @param source Le point (noeud) de depart
 * @param cible Le point (noeud) d'arrivee
 * @param chemin Le chemin trouve a la fin de dijkstra
 * @param n La taille totale de la matrice du labyrinthe
 * @return bool_t True si reussi, false sinon
 */
bool_t dijkstra(couples_graphe_t graphe, int source, int cible, liste_t *chemin, int n);

void checkVoisin(int voisinCourant, node_t cour, arete_t areteVoisin, int *prec, bool_t *traite, binary_heap_t *tas);

void checkVoisinAstar(int numvoisin, node_t cour, arete_t areteVoisin, int *prec, bool_t *traite, binary_heap_t *tas, int cible, int n);

/**
 * @brief Calcule la distance de manhattan
 * 
 * @param courx 
 * @param coury 
 * @param ciblex 
 * @param cibley 
 * @return int 
 */
int manhattan(int courx, int coury, int ciblex, int cibley);

/**
 * @brief Applique l'algorithme A* sur un graphe
 * 
 * @param graphe Le graphe 
 * @param source Le point (noeud) de depart
 * @param cible Le point (noeud) d'arrivee
 * @param chemin Le chemin trouve a la fin de A*
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @return bool_t True si reussi, false sinon
 */
bool_t astar(couples_graphe_t graphe, int source, int cible, liste_t *chemin, int n, int m);

/**
 * @brief Effectue un parcours en profondeur sur un graphe (avec affichage au fur et a mesure)
 * 
 * @param graph Le graphe
 * @param debut Point de depart du parcours
 * @param renderer Le rendu
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @param tile Rectangle representant une case du labyrinthe
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param texture La texture pour les sols et les murs
 * @param grille La grille representant le labyrinthe
 * @param destPerso Le rectangle pour le personnage
 * @param perso La texture a appliquer au personnage
 * @param delai Le delai pour afficher chaque etape du parcours
 */
void parcoursEnProfondeur(couples_graphe_t graph, int debut, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso, int delai);

/**
 * @brief Initialise un tableau de marque a false
 * 
 * @param marques Tableau de booleens
 * @param n Taille du tableau
 */
void initialiserMarque(bool_t *marques, int n);

/**
 * @brief Permet d'explorer les fils d'un noeud pour le parcours en profondeur
 * 
 * @param graph Le graphe
 * @param s Noeud de depart
 * @param marques Tableau de booleens
 * @param renderer Le rendu
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @param tile Rectangle representant une case du labyrinthe
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param texture La texture pour les sols et les murs
 * @param grille La grille representant le labyrinthe
 * @param destPerso Le rectangle pour le personnage
 * @param perso La texture a appliquer au personnage
 * @param delai Le delai pour afficher chaque etape du parcours
 */
void explorer(couples_graphe_t graph, int s, bool_t *marques, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso, int delai);

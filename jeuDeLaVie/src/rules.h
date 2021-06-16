#include <stdio.h>
#include "matrice.h"
#include "booleen.h"

#define TAILLE 9

typedef struct {
	booleen_t survie[TAILLE];
	booleen_t naissance[TAILLE];
} rule_t;

/**
 * @brief Initialise les regles de vie
 * 
 * @param life regles
 */
void initLife(rule_t *life);

/**
 * @brief Initialise les regles de labyrinthe
 * 
 * @param maze regles
 */
void initMaze(rule_t *maze); 

/**
 * @brief Donne le nombre de voisins d'une cellule
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 * @param i indice ligne de la cellule
 * @param j indice colonne de la cellule
 * @return int 
 */
int getNeighbours(int ** grid, int n, int m, int i, int j);

/**
 * @brief Fait evoluer la matrice selon les regles
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 * @param rule regles
 */
void nextIteration(int *** grid, int n, int m, rule_t *rule);
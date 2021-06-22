#pragma once

#include "partition.h"
#include "graphviz.h"
#include <time.h>

typedef int *graphe_t;

/** 
 * @brief cree un graphe a partir d'un matrice d'adjacence
 * @param n la taille de la matrice
 */
graphe_t createAdjencyMatrix(int n);

/** 
 * @brief affiche une matrice d'adjacence
 * @param matrix la matrice
 * @param n la taille de la matrice
 */
void afficherMatriceAdjacence(graphe_t matrix, int n);


/** 
 * @brief dessine un graphe dans ../graphviz/graphe.png
 * @param graphe le graphe
 * @param n la taille de la matrice d'adjacence du graphe
 */
void afficherGraphe(graphe_t graphe, int n);

/** 
 * @brief Calcule les noeuds de chacune des composantes connexes du graphe
 * @param graphe le graphe
 * @param n la taille de la matrice d'adjacence du graphe
 * @param noeudsI le nombre de composantes connexes
 * @return la liste des tableaux d'elements de chaque composante connexe
 */
element_t** noeudsCompoConnexes(graphe_t graphe, int n, int * noeudsI);

/** 
 * @brief affiche le sous-graphe specifie d'un graphe
 * @param graphe le graphe
 * @param n la taille de la matrice d'adjacence du graphe
 */
void afficherSousGraphe(graphe_t graphe, element_t* sgraphe);

/** 
 * @brief pratitionne un graphe en ses composantes connexes
 * @param graphe le graphe
 * @param n la taille de la matrice d'adjacence du graphe
 * @return la partition des composantes connexes
 */
partition_t grapheToPartition(graphe_t graphe, int n);
void afficherNoeudsCompoConnexes(element_t ** noeuds, int n_noeuds, int n);
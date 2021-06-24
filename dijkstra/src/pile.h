             /**********************************************************/
             /*Chandeze Marius & Meunier Killian                  2021 */
             /*--------------------------------------------------------*/
             /*                      pile.h                            */
             /*                 Traitement d'une pile                  */
             /*                   FICHIER D'ENTETE                     */
             /**********************************************************/

#ifndef PILE_H_
#define PILE_H_

#include <stdio.h>
#include <stdlib.h>
#include "bool.h"

/************************************/
/* Type d'éléments dans la pile     */
/************************************/
typedef int typePile;

/**************************************/
/* Format des éléments dans la pile   */
/**************************************/
#define FORMAT "%d"

/***************************/
/* Structure d'une pile    */
/***************************/
typedef struct pile
{
    int nb_max;
    int rg_sommet;
    typePile * base;
}pile_t;

/**************************************************/
/* Initialisation d'une pile de taille 'taille'   */
/**************************************************/
pile_t * initPile(int taille);

/****************************************/
/* Libere l'espace memoire d'une pile   */
/****************************************/
void libererPile(pile_t * pile);

/**********************************/
/* Verifie si une pile est vide   */
/**********************************/
int estVidePile(pile_t pile);

/************************************/
/* Verifie si une pile est pleine   */
/************************************/
int estPleinePile(pile_t pile);

/*****************************************************/
/* Renvoie dans adr la valeur du sommet de la pile   */
/*****************************************************/
bool_t sommetPile(pile_t pile, typePile * adr);

/************************************/
/* Empile une valeur dans la pile   */
/************************************/
bool_t empiler(pile_t * pile, typePile val);

/****************************************/
/* Depile l'element en sommet de pile   */
/****************************************/
bool_t depiler(pile_t * pile, typePile * val);

/****************************************/
/* Affiche une pile dans le terminal    */
/****************************************/
void afficherPile(pile_t pile);

#endif

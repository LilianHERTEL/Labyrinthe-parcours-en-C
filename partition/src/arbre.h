             /**********************************************************/
             /*Chandeze Marius & Meunier Killian                  2021 */
             /*--------------------------------------------------------*/
             /*                        arbre.h                         */
             /*                 Traitement d'un arbre                  */
             /*                   FICHIER D'ENTETE                     */
             /**********************************************************/

#ifndef ARBRE_H_
#define ARBRE_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "booleen.h"

/************************************/
/* Type d'éléments dans l'arbre     */
/************************************/
typedef char typeElemArbre;

/**************************************/
/* Format des éléments dans l'arbre   */
/**************************************/
#define FORMAT_ARBRE "%c"

/***************************/
/* Structure d'un arbre    */
/***************************/
typedef struct noeud_t
{
    typeElemArbre v;
    struct noeud_t * fils; // Lien vertical
    struct noeud_t * frere; // Lien horizontal
}noeud_t, * arbre_t;


/***************************************/
/* Initialisation d'un arbre a NULL    */
/***************************************/
noeud_t * initialisation_arbre();

/********************************************/
/* Creer un noeud a partir d'une valeur     */
/********************************************/
noeud_t * creerNoeud(typeElemArbre val);

/**********************************************************************************************/
/* Retrouve le noeud precedent d'une valeur donnee dans une liste triee (liens horizontaux)   */
/**********************************************************************************************/
arbre_t * recherche_prec_triee(arbre_t * arbre, char val, booleen_t * trouve);

/********************************************************/
/* Ajoute un noeud dans une liste (liens horizontaux)   */
/********************************************************/
void ajout_lien_horizontal(arbre_t * arbre, noeud_t * elt);

#endif

             /**********************************************************/
             /*Chandeze Marius & Meunier Killian                  2021 */
             /*--------------------------------------------------------*/
             /*                        arbre.c	                       */
             /*                 Traitement d'un arbre                  */
             /*               Module avec fonctions de base            */
             /**********************************************************/

#include "arbre.h"

/**************************************************************************/
/* Initialise un arbre a NULL                                             */
/*                                                                        */
/* Principe :                                                             */
/* Retourner NULL                                                         */
/*                                                                        */
/* Lexique :                                                              */
/**************************************************************************/
noeud_t * initialisation_arbre()
{
    return NULL;
}

/**************************************************************************/
/* Creer un noeud a partir d'une valeur                                 */
/*                                                                        */
/* Principe :                                                             */
/* Alloue de l'espace pour un noeud                                     */
/* Si l'espace pour ce noeud a bien ete reserve                         */
/*   On met la valeur en parametre dans le noeud                        */
/*   et on met son frere et son fils a null                                         */
/* Retourner le noeud cree                                              */
/* IMPORTANT : Penser a verifier le noeud apres appel de cette fonction */
/*                                                                        */
/* Lexique :                                                              */
/* val : valeur que contiendra le noeud                                 */
/**************************************************************************/
noeud_t * creerNoeud(typeElemArbre val)
{
    noeud_t   * elt;

    elt = (noeud_t *)malloc(sizeof(noeud_t));
    if(elt)
    {
        elt->v = val;
        elt->fils = NULL;
        elt->frere = NULL;
    }

    return elt;
}

/**************************************************************************/
/* Recherche du noeud precedant une valeur donnee dans une liste de liens,*/
/* horizontaux dans l'ordre croissant (arbre de caracteres)               */
/*                                                                        */
/* Principe :                                                             */
/* Parcourir la liste avec 2 pointeurs                                    */
/* Un pour le precedent et un pour le courant                             */
/* Si on trouve la valeur donnee, on renvoie le noeud precedent           */
/* Sinon, on renvoie la valeur d'insertion                                */
/*                                                                        */
/* Lexique :                                                              */
/* liste : liste de caracteres trie dans l'ordre croissant                */
/* val : valeur contenu dans le noeud dont on veut le precedent           */
/* trouve : booleen qui permet de dire si on a trouve cette valeur        */
/**************************************************************************/
arbre_t * recherche_prec_triee(arbre_t * liste, char val, booleen_t * trouve)
{
    noeud_t    * tmp;
    arbre_t      * prec;

    tmp = *liste;
    prec = liste;

    while(tmp && tolower(tmp->v) < tolower(val))
    {
        prec = &(tmp->fils);
        tmp = tmp->fils;
    }

    if(tmp && tmp->v == val)
    {
        *trouve = true;
    }
    else    
    {
        *trouve = false; 
    }

    return prec;
}

/**************************************************************************/
/* Ajout d'un noeud dans une liste (lien horizontaux) (ajout LCH)         */
/*                                                                        */
/* Principe :                                                             */
/* Definir le suivant du noeud a ajouter comme le suivant de noeud ou     */
/* on veut ajouter ce nouveau noeud                                       */
/* Puis, remplacer le noeud ou on veut faire l'insertion par le nouveau   */
/*                                                                        */
/* Lexique :                                                              */
/* arbre : pointeur sur le noeud qui va etre la position du nouveau noeud */
/* elt : nouveau noeud a inserer                                          */
/**************************************************************************/
void ajout_lien_horizontal(arbre_t * arbre, noeud_t * elt)
{
    elt->frere = *arbre;
    *arbre = elt;
}
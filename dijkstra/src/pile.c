             /**********************************************************/
             /*Chandeze Marius & Meunier Killian                  2021 */
             /*--------------------------------------------------------*/
             /*                     	pile.c	                       */
             /*              	 Traitement d'une pile                 */
             /*               Module avec fonctions de base            */
             /**********************************************************/

#include "pile.h"

/**************************************************************************/
/* Initialise une pile de taille 'taille'                                 */
/*                                                                        */
/* Principe :                                                             */
/* allouer de l'espace pour la tete pile                                  */
/* Si il n'y a pas d'erreur,											  */
/* 	On defini la taille max de la pile,  								  */
/*	le rang de son sommet a -1 car il n'y a pas encore de sommet. 		  */
/*  Et on alloue un espace de taille 'taille' pour la pile				  */
/* Renvoie la pile cree, ou null si il y a eu une erreur				  */
/*                                                                        */
/* Lexique :                                                              */
/* taille : taille maximum de la pile									  */
/**************************************************************************/
pile_t * initPile(int taille)
{
	pile_t 		* pile;

	pile = (pile_t *)malloc(sizeof(pile_t));
	if(pile)
	{
		pile->nb_max = taille;
		pile->rg_sommet = -1;
		pile->base = (typePile *)malloc(sizeof(typePile) * taille);
		if(pile->base == NULL)
		{
			free(pile);
			pile = NULL;
		}
	}
	return pile;
}

/**************************************************************************/
/* Libere l'espace memoire alloue a la pile en parametre                  */
/*                                                                        */
/* Principe :                                                             */
/* Liberer l'espace de la pile						      				  */
/* Puis liberer l'espace de la tete de la pile		     				  */
/*                                                                        */
/* Lexique :                                                              */
/* pile : pile a liberer											      */
/**************************************************************************/
void libererPile(pile_t * pile)
{
	free(pile->base);
	free(pile);
	pile = NULL;
}

/**************************************************************************/
/* Verifie si la pile en parametres est vide			                  */
/*                                                                        */
/* Principe :                                                             */
/* Comparer le rang du sommet avec -1 (-1 : il n'y a pas de sommet)		  */
/* Retourne true si la pile est vide et false sinon	     				  */
/*                                                                        */
/* Lexique :                                                              */
/* pile : la pile a verifier										      */
/**************************************************************************/
int estVidePile(pile_t pile)
{
	return (pile.rg_sommet == -1);
}

/**************************************************************************/
/* Verifie si la pile en parametres est pleine			                  */
/*                                                                        */
/* Principe :                                                             */
/* Comparer le rang du sommet avec la taille maximum de la pile			  */
/* Retourne true si la pile est pleine et false sinon	     			  */
/*                                                                        */
/* Lexique :                                                              */
/* pile : la pile a verifier										      */
/**************************************************************************/
int estPleinePile(pile_t pile)
{
	return (pile.rg_sommet == pile.nb_max - 1);
}

/**************************************************************************/
/* Recupere la valeur du sommet de la pile                                */
/*                                                                        */
/* Principe :                                                             */
/* Verifier que la pile n'est pas vide                                    */
/* Si elle n'est pas vide,   											  */
/* 	On recupere la valeur de son sommet  								  */
/* Renvoie false si la pile est vide, true sinon avec la valeur du sommet */
/*                                                                        */
/* Lexique :                                                              */
/* pile : une pile														  */
/* adr : adresse ou l'on va stocker l'element en sommet de pile			  */
/**************************************************************************/
bool_t sommetPile(pile_t pile, typePile * adr)
{
	bool_t 	etat = false;

	if(! estVidePile(pile))
	{
		*adr = *(pile.base + pile.rg_sommet);
		etat = true;
	}

	return etat; 
}

/**************************************************************************/
/* Empile une valeur dans la pile	                                      */
/*                                                                        */
/* Principe :                                                             */
/* Verifier que la pile n'est pas pleine                                  */
/* Si elle n'est pas pleine,   											  */
/* 	On incremente la rang du sommet,  								  	  */
/*  Puis on insere la nouvelle valeur dans l'emplacement du nouveau sommet*/
/* Renvoie false si la pile est pleine, true sinon 						  */
/*                                                                        */
/* Lexique :                                                              */
/* pile : une pile														  */
/* val : la valeur a empiler											  */
/**************************************************************************/
bool_t empiler(pile_t * pile, typePile val)
{
	bool_t 	etat = false;

	if(! estPleinePile(*pile))
	{
		pile->rg_sommet = pile->rg_sommet + 1;
		*(pile->base + pile->rg_sommet) = val;
		etat = true;
	}

	return etat;
}

/**************************************************************************/
/* Depile l'element en sommet de pile                                     */
/*                                                                        */
/* Principe :                                                             */
/* Verifier que la pile n'est pas vide                                    */
/* Si elle n'est pas vide,   											  */
/* 	On recupere la valeur du sommet,  								  	  */
/*  Puis on decremente le rang du sommet 								  */
/* Renvoie false si la pile est vide, true sinon avec la valeur du sommet */
/*                                                                        */
/* Lexique :                                                              */
/* pile : une pile														  */
/* adr : adresse ou l'on va stocker l'element en sommet de pile			  */
/**************************************************************************/
bool_t depiler(pile_t * pile, typePile * val)
{
	bool_t 	etat = false;

	if(! estVidePile(*pile))
	{
		*val = *(pile->base + pile->rg_sommet);
		pile->rg_sommet = pile->rg_sommet - 1;
		etat = true;
	}

	return etat;
}

/**************************************************************************/
/* Affiche une pile dans le terminal                                      */
/*                                                                        */
/* Principe :                                                             */
/* Parcourir la pile en partant du sommet vers la base                    */
/* Afficher chaque valeur de la pile   							     	  */
/*                                                                        */
/* Lexique :                                                              */
/* pile : une pile														  */
/**************************************************************************/
void afficherPile(pile_t pile)
{
	int 	i;

	for(i = pile.rg_sommet; i >= 0; i--)
	{
		printf("|"FORMAT"|\n", *(pile.base + i));
	}
	printf("\n");
}

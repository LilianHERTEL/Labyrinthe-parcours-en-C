#include "dijkstra.h"

bool dijkstra(graphe_t graphe, int source, int cible, int *chemin, int n) {
	binary_heap_t tas;
	bool found = false;
	noeud_t cour, voisin, *prec;
	float newdist;

	tas.array = malloc(sizeof(int) * n);
	prec = malloc(sizeof(noeud_t) * n);
	if(prec == NULL || tas.array == NULL) {
		fputs("erreur malloc dijkstra\n", stderr);
		return false;
	}
	tas.length = n;
	tas.heapSize = n;
	
	//initialisation du tas
	for(i = 0; i < n; ++i) {
		tas.array[i].num = i;
		tas.array[i].dist = FLT_MAX;
		//dist[graphe[] = INT_MAX;
		//prec[i] = -1;
	}
	tas.array[source] = 0;

	//boucle principale tant qu'on a pas trouve et que le tas n'est pas vide
	while(found == false && tas.heapSize != 0) {
		
		//on prend le premier de la file d'attente
        	cour = heap_minimum(tas);

		//tant qu'on n'a pas atteint la cible
		if(cour.num != cible) {

			//pour tous les voisins du noeud courant
			for(i = 0; i < n; ++i) {
				if(graphe.aretes[i].noeudDeb == cour.num) {
					/*
					 * vu qu'on a mis tous les voisins au debut, pas besoin de verifier
					 *
					//si le voisin est dans le tas
					if(getFromHeap(graphe.aretes[i].noeudFin, &voisin)) {
					*/
						//on calcule la distance de la source au voisin en passant par le noeud courant
						newdist = (graphe.aretes[cour.num].poids + graphe.aretes[tas.array[voisin]].poids / 2.0) + cour.dist;

						//si elle est plus courte que la distance precedente, alors on la remplace
						if(tas.array[voisin].dist > newdist) {
							//prev[v] = u;
							tas.array[voisin].dist = newdist;
						}
					/*
					}
					
					else {
						//ajouter le voisin au tas
					}
					*/
				}
			}
		}
		else {
			found == true;
			//nettoyer
		}
	}

	free(tas.array);
	return found;
}

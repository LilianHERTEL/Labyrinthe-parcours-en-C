#include "dijkstra.h"

bool dijkstra(graphe_t graphe, int source, int cible, int *chemin, int n) {
	binary_heap_t tas;
	bool found = false;
	int *dist, *liste, *prec;
	noeud_t cour, voisin;

	tas.array = malloc(sizeof(int) * n);
	//liste = malloc(sizeof(int) * n);
	//prec = malloc(sizeof(int) * n);
	//dist = malloc(sizeof(int) * n);
	if(liste == NULL || prec == NULL || dist == NULL) {
		fputs("erreur malloc dijkstra\n", stderr);
		return false;
	}
	tas.length = n;
	tas.heapSize = n;
	
	for(i = 0; i < n; ++i) {
		tas.array[i].num = i;
		tas.array[i].dist = INT_MAX;
		//dist[graphe[] = INT_MAX;
		//prec[i] = -1;
	}
	tas.array[source] = 0;
	while(found == false && tas.heapSize != 0) {
        	cour = heap_minimum(tas);
		if(cour.num != cible) {
			for(i = 0; i < n; ++i) {//for each neighbor v of u
				if(graphe.aretes[i].noeudDeb == cour.num) {
					if(getFromHeap(graphe.aretes[i].noeudFin, &voisin)) {
						newdist = (graphe.aretes[cour.num].poids + graphe.aretes[tas.array[voisin]].poids / 2.0) + cour.dist;
						if(tas.array[voisin].dist > newdist) {
							//prev[v] = u;
							tas.array[voisin].dist = newdist;
						}
					}
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

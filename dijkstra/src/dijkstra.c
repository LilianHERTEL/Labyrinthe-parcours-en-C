#include "dijkstra.h"

bool_t dijkstra(couples_graphe_t graphe, int source, int cible, int *chemin, int n) {
	binary_heap_t tas;
	bool_t found = false;
	node_t cour, noeudVoisin;
	float newdist;
	int k = 0, u, voisin, *prec, i;

	//initialisation
	tas.array = malloc(sizeof(int) * n);
	prec = malloc(sizeof(int) * n);
	chemin = malloc(sizeof(int) * n);
	if(chemin == NULL || tas.array == NULL || prec == NULL) {
		fputs("erreur malloc dijkstra\n", stderr);
		return false;
	}
	memset(prec, -1, sizeof(int) * n);

	tas.length = n;
	tas.heapSize = n;

	/*
	 * inutile si on insert au fur et a mesure
	 *
	//initialisation du tas
	for(i = 0; i < n; ++i) {
		tas.array[i].num = i;
		tas.array[i].dist = FLT_MAX;
		//dist[graphe[] = INT_MAX;
		//prec[i] = -1;
	}
	*/

	//on insert d'abord la source
	cour.num = source;
	cour.dist = 0;
	minHeapInsert(&tas, cour);

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
					 * si on met tous les voisins au debut, pas besoin de verifier
					 */
					//si le voisin est dans le tas
					if(isInHeap(tas, graphe.aretes[i].noeudFin, &voisin)) {
					
						//on calcule la distance de la source au voisin en passant par le noeud courant
						newdist = graphe.aretes[i].poids + cour.dist;

						//si elle est plus courte que la distance precedente, alors on la remplace
						if(tas.array[voisin].dist > newdist) {

							//on definit le noeud courant en tant que precedent du voisin
							prec[tas.array[voisin].num] = cour.num;

							//on met a jour sa distance
							tas.array[voisin].dist = newdist;
						}
					}

					//si le voisin n'est pas dans le tas
					else {
						//ajouter le voisin au tas
						noeudVoisin.num = graphe.aretes[i].noeudFin;
						noeudVoisin.dist = graphe.aretes[i].poids + cour.dist;
						minHeapInsert(&tas, noeudVoisin);
					}
				}
			}
		}
		else {
			//cible trouvee
			found = true;
		}
	}

	//on remonte le tableau des precedents en partant de la cible
	u = cible;
	if(prec[u] != -1 || u == source) {
		while(prec[u] != -1) {
			//on ajoute le numero courant
			chemin[k] = prec[u];
			u = prec[u];
			++k;
		}
	}

	free(prec);
	free(tas.array);
	return found;
}

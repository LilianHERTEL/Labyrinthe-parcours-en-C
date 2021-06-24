#include "parcours.h"

bool_t dijkstra(couples_graphe_t graphe, int source, int cible, liste_t *chemin, int n) {
	binary_heap_t tas;
	bool_t found = false;
	node_t cour, noeudVoisin;
	maillon_t *maillon;
	float newdist;
	int u, voisin, *prec, i;

	printf("cible %d\n", cible);
	//initialisation
	tas.array = malloc(sizeof(int) * n);
	prec = malloc(sizeof(int) * n);
	*chemin = initialisation_liste();
	if(tas.array == NULL || prec == NULL) {
		fputs("erreur malloc dijkstra\n", stderr);
		return false;
	}
	for(i = 0; i < n; ++i) {
		prec[i] = -1;
	}
	tas.length = n;
	tas.heapSize = 0;

	/*
	 * inutile si on insert au fur et a mesure
	 *
	//initialisation du tas
	for(i = 0; i < nbaretes; ++i) {
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
        cour = heapExtractMin(&tas);
        fprintf(stderr, "on passe a %d de distance %f\n", cour.num, cour.dist);
        //printHeap(tas);
        if(cour.num == -1) {
            puts("erreur");
            free(prec);
            free(tas.array);
            return false;
        }
		//on n'a pas atteint la cible
		if(cour.num != cible) {
			puts("cible non atteinte\n");

			//pour tous les voisins du noeud courant
			for(i = 0; i < graphe.nbAretes; ++i) {
				//fprintf(stderr, "on check si %d est dans %d -> %d\n", cour.num, graphe.aretes[i].noeudDeb, graphe.aretes[i].noeudFin);
				if(graphe.aretes[i].noeudDeb == cour.num) {
					puts("c'est OK");
					/*
					* si on met tous les voisins au debut, pas besoin de verifier
					*/
					//si le voisin est dans le tas
					if(isInHeap(tas, graphe.aretes[i].noeudFin, &voisin)) {
						puts("voisin dans le tas");
						printf("voisin %d\n", voisin);
					
						//on calcule la distance de la source au voisin en passant par le noeud courant
						newdist = graphe.aretes[i].poids + cour.dist;

						//si elle est plus courte que la distance precedente, alors on la remplace
						if(tas.array[voisin].dist > newdist) {
							puts("changement de voisin");
							//on definit le noeud courant en tant que precedent du voisin
							prec[tas.array[voisin].num] = cour.num;

							//on met a jour sa distance
							tas.array[voisin].dist = newdist;
						}
					}

					//si le voisin n'est pas dans le tas
					else {
						puts("voisin pas dans le tas");
						//ajouter le voisin au tas
						fprintf(stderr, "on ajoute %d au tas\n", graphe.aretes[i].noeudFin);
						noeudVoisin.num = graphe.aretes[i].noeudFin;
						noeudVoisin.dist = graphe.aretes[i].poids + cour.dist;
						minHeapInsert(&tas, noeudVoisin);
						//on definit le noeud courant en tant que precedent du voisin
						prec[noeudVoisin.num] = cour.num;
					}
				}
				else {
					if(graphe.aretes[i].noeudFin == cour.num) {
						puts("c'est OK");
						//si le voisin est dans le tas
						if(isInHeap(tas, graphe.aretes[i].noeudDeb, &voisin)) {
							puts("voisin dans le tas");
							printf("voisin %d\n", voisin);
							//on calcule la distance de la source au voisin en passant par le noeud courant
							newdist = graphe.aretes[i].poids + cour.dist;

							//si elle est plus courte que la distance precedente, alors on la remplace
							if(tas.array[voisin].dist > newdist) {
								puts("changement de voisin");

								//on definit le noeud courant en tant que precedent du voisin
								prec[tas.array[voisin].num] = cour.num;

								//on met a jour sa distance
								tas.array[voisin].dist = newdist;
							}
						}
						else {
							//si le voisin n'est pas dans le tas
							puts("voisin pas dans le tas");
							//ajouter le voisin au tas
							fprintf(stderr, "on ajoute %d au tas\n", graphe.aretes[i].noeudDeb);
							noeudVoisin.num = graphe.aretes[i].noeudDeb;
							noeudVoisin.dist = graphe.aretes[i].poids + cour.dist;
							minHeapInsert(&tas, noeudVoisin);
							//on definit le noeud courant en tant que precedent du voisin
							prec[noeudVoisin.num] = cour.num;
						}
					}
				}
			}
			puts("***");
		}
		else {
            puts("cible trouvee");
			//cible trouvee
			found = true;
			//prec[cible] = cour.num;
		}
        puts("\n");
	}

	//on remonte le tableau des precedents en partant de la cible
	u = cible;
	printf("prec[u] = %d\n", prec[u]);
	for(i = 0; i < n; ++i) {
		printf("prec[%d] = %d\n", i, prec[i]);
	}
	if((prec[u] != -1 || u == source) && found == true) {
		while(prec[u] != -1) {
			//on ajoute le numero courant
			//chemin[k] = prec[u];
			printf("u : %d, prec[u] = %d\n", u, prec[u]);
			maillon = creerMaillon(prec[u]);
			ajout_lch(chemin, maillon);
			u = prec[u];
			//++k;
		}
	}
    else {
        fputs("cible pas trouvee\n", stderr);
	    free(prec);
    	free(tas.array);
        return false;
    }

	free(prec);
	free(tas.array);
	return found;
}

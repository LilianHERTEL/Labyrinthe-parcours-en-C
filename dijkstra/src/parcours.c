#include "parcours.h"

bool_t dijkstra(couples_graphe_t graphe, int source, int cible, liste_t *chemin, int n)
{
	binary_heap_t tas;
	bool_t found = false, *traite;
	node_t cour, noeudVoisin;
	maillon_t *maillon;
	float newdist;
	int u, voisin, *prec, i;

	printf("cible %d\n", cible);
	//initialisation
	tas.array = malloc(sizeof(int) * n);
	prec = malloc(sizeof(int) * n);
	*chemin = initialisation_liste();
	traite = malloc(sizeof(int) * n);
	if(tas.array == NULL || prec == NULL) {
		fputs("erreur malloc dijkstra\n", stderr);
		return false;
	}
	for(i = 0; i < n; ++i) {
		prec[i] = -1;
		traite[i] = false;
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
	while (found == false && tas.heapSize != 0)
	{

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
		traite[cour.num] = true;
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
						
						fprintf(stderr, "on ajoute %d au tas\n", graphe.aretes[i].noeudFin);
						noeudVoisin.num = graphe.aretes[i].noeudFin;
						noeudVoisin.dist = graphe.aretes[i].poids + cour.dist;
						
						if(traite[noeudVoisin.num] == false) {
							//ajouter le voisin au tas
							minHeapInsert(&tas, noeudVoisin);
							//on definit le noeud courant en tant que precedent du voisin
							prec[noeudVoisin.num] = cour.num;
						}
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
							if(traite[noeudVoisin.num] == false) {
							//ajouter le voisin au tas
							minHeapInsert(&tas, noeudVoisin);
							//on definit le noeud courant en tant que precedent du voisin
							prec[noeudVoisin.num] = cour.num;
						}
						}
					}
				}
			}
			puts("***");
		}
		else
		{
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
	if((prec[u] != -1 || u == source)) {
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
    }

	free(prec);
	free(tas.array);
	return found;
}

void parcoursEnProfondeur(couples_graphe_t graph, int debut, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso)
{
	bool_t *marques;

	marques = (bool_t *)malloc(sizeof(bool_t) * graph.nbNoeuds);
	if (marques)
	{
		initialiserMarque(marques, graph.nbNoeuds);
		explorer(graph, debut, marques, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso);
	}
	else
	{
		fprintf(stderr, "Erreur malloc\n");
	}
}

void initialiserMarque(bool_t *marques, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		marques[i] = false;
	}
}

void explorer(couples_graphe_t graph, int s, bool_t *marques, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso)
{
	int *voisins,
		nbVoisins,
		i;

	marques[s] = true;

	//affichage
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
	drawLab(renderer, grille, n, m, tile, positionLab, texture);
	drawChemin(renderer, n, m, tile, positionLab, texture, marques, graph.nbNoeuds);
	destPerso.x = positionLab.x + tile.w * (s - (s/n) * m) + tile.w * 0.1;
	destPerso.y = positionLab.y + tile.h * (s/n) + tile.h * 0.1;
	drawperso(renderer, perso, destPerso);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	SDL_Delay(100);

	voisins = trouverVoisins(graph, s, &nbVoisins);
	for (i = 0; i < nbVoisins; i++)
	{
		if (marques[voisins[i]] == false)
		{
			explorer(graph, voisins[i], marques, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
			drawLab(renderer, grille, n, m, tile, positionLab, texture);
			drawChemin(renderer, n, m, tile, positionLab, texture, marques, graph.nbNoeuds);
			destPerso.x = positionLab.x + tile.w * (s - (s/n) * m) + tile.w * 0.1;
			destPerso.y = positionLab.y + tile.h * (s/n) + tile.h * 0.1;
			drawperso(renderer, perso, destPerso);
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			SDL_Delay(100);
		}
	}
}
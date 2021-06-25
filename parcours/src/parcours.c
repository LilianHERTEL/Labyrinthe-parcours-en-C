#include "parcours.h"

/**
 * @brief Applique l'algorithme de dijkstra sur un graphe
 * 
 * @param graphe Le graphe 
 * @param source Le point (noeud) de depart
 * @param cible Le point (noeud) d'arrivee
 * @param chemin Le chemin trouve a la fin de dijkstra
 * @param n La taille totale de la matrice du labyrinthe
 * @return bool_t True si reussi, false sinon
 */
bool_t dijkstra(couples_graphe_t graphe, int source, int cible, liste_t *chemin, int n)
{
	binary_heap_t tas;
	bool_t found = false, *traite;
	node_t cour;
	maillon_t *maillon;
	int u, *prec, i;

	printf("cible %d\n", cible);
	//initialisation
	tas.array = malloc(sizeof(int) * n);
	prec = malloc(sizeof(int) * n);
	*chemin = initialisation_liste();
	traite = malloc(sizeof(int) * n);
	if (tas.array == NULL || prec == NULL || traite == NULL)
	{
		fputs("erreur malloc dijkstra\n", stderr);
		return false;
	}
	for (i = 0; i < n; ++i)
	{
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
	while (found == false && tas.heapSize > 0)
	{

		//on prend le premier de la file d'attente
		cour = heapExtractMin(&tas);
		fprintf(stderr, "on passe a %d de distance %f\n", cour.num, cour.dist);
		//printHeap(tas);
		if (cour.num == -1)
		{
			puts("erreur");
			free(traite);
			free(prec);
			free(tas.array);
			return false;
		}
		traite[cour.num] = true;
		//on n'a pas atteint la cible
		if (cour.num != cible)
		{
			puts("cible non atteinte\n");

			//pour tous les voisins du noeud courant
			for (i = 0; i < graphe.nbAretes; ++i)
			{
				//fprintf(stderr, "on check si %d est dans %d -> %d\n", cour.num, graphe.aretes[i].noeudDeb, graphe.aretes[i].noeudFin);
				if (graphe.aretes[i].noeudDeb == cour.num)
				{
					puts("debut");
					checkVoisin(graphe.aretes[i].noeudFin, cour, graphe.aretes[i], prec, traite, &tas);
				}
				else if (graphe.aretes[i].noeudFin == cour.num)
				{
					puts("fin");
					checkVoisin(graphe.aretes[i].noeudDeb, cour, graphe.aretes[i], prec, traite, &tas);
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
	for (i = 0; i < n; ++i)
	{
		printf("prec[%d] = %d\n", i, prec[i]);
	}
	if ((prec[u] != -1 || u == source))
	{
		while (prec[u] != -1)
		{
			//on ajoute le numero courant
			//chemin[k] = prec[u];
			printf("u : %d, prec[u] = %d\n", u, prec[u]);
			maillon = creerMaillon(prec[u]);
			ajout_lch(chemin, maillon);
			u = prec[u];
			//++k;
		}
	}
	else
	{
		fputs("cible pas trouvee\n", stderr);
	}

	free(traite);
	free(prec);
	free(tas.array);
	return found;
}

/**
 * @brief traitement effectue sur chaque voisin du noeud courant
 * 
 * @param debfin le voisin du noeud courant (debut ou fin de l'arrete dans le graphe)
 * @param cour noeud courant
 * @param areteVoisin l'arete entre le neoud courant et le voisin traite
 * @param prec tableau des precedents de chaque noeud
 * @param traite tableau de traitement des neouds
 * @param tas file de priorite sous forme de tas binaire
 */
void checkVoisin(int debfin, node_t cour, arete_t areteVoisin, int *prec, bool_t *traite, binary_heap_t *tas)
{
	int voisin;
	float newdist;
	node_t noeudVoisin;
	/*
	* si on met tous les voisins au debut, pas besoin de verifier
	*/
	//si le voisin est dans le tas
	if (isInHeap(*tas, debfin, &voisin))
	{
		puts("voisin dans le tas");
		printf("voisin %d\n", voisin);

		//on calcule la distance de la source au voisin en passant par le noeud courant
		newdist = areteVoisin.poids + cour.dist;

		//si elle est plus courte que la distance precedente, alors on la remplace
		if (tas->array[voisin].dist > newdist)
		{
			puts("changement de voisin");
			//on definit le noeud courant en tant que precedent du voisin
			prec[debfin] = cour.num;

			//on met a jour sa distance
			tas->array[voisin].dist = newdist;
		}
	}
	//si le voisin n'est pas dans le tas
	else
	{
		puts("voisin pas dans le tas");
		fprintf(stderr, "on ajoute %d au tas\n", debfin);

		if (traite[debfin] == false)
		{
			noeudVoisin.num = debfin;
			noeudVoisin.dist = areteVoisin.poids + cour.dist;
			//ajouter le voisin au tas
			minHeapInsert(tas, noeudVoisin);
			//on definit le noeud courant en tant que precedent du voisin
			prec[debfin] = cour.num;
		}
	}
	puts("");
}

/**
 * @brief effectue le traitement pour astar sur un voisin du noeud courant
 * 
 * @param numvoisin numero du voisin traite
 * @param cour noeud courant
 * @param areteVoisin arete du graphe entre le neoud courant et le voisin traite
 * @param prec tableau des precedents des noeuds
 * @param traite tableau des noeuds traites
 * @param tas file de priorite implemente avec un tas binaire
 * @param cible noeud a atteindre
 * @param n hauteur de la matrice du graphe
 */
void checkVoisinAstar(int numvoisin, node_t cour, arete_t areteVoisin, int *prec, bool_t *traite, binary_heap_t *tas, int cible, int n)
{
	int voisinTas;
	node_t noeudVoisin;

	//on calcule la distance de la source au voisin en passant par le noeud courant
	noeudVoisin.num = numvoisin;
	noeudVoisin.distcible = manhattan(numvoisin % n, numvoisin / n, cible % n, cible / n);
	noeudVoisin.distsource = cour.distsource + areteVoisin.poids;
	//((graphe[cour.num % n][cour.num / n] + graphe[numvoisin % n][numvoisin / n]) / 2.0);
	noeudVoisin.dist = noeudVoisin.distcible + noeudVoisin.distsource;

	//si le voisin est dans le tas
	if (isInHeap(*tas, numvoisin, &voisinTas))
	{
		puts("voisin dans le tas");
		printf("voisin %d\n", voisinTas);

		//si elle est plus courte que la distance precedente, alors on la remplace
		if (tas->array[voisinTas].dist > noeudVoisin.dist)
		{
			puts("changement de voisin");
			//on definit le noeud courant en tant que precedent du voisin
			prec[numvoisin] = cour.num;

			//on met a jour sa distance
			tas->array[voisinTas] = noeudVoisin;
		}
	}
	//si le voisin n'est pas dans le tas
	else
	{
		puts("voisin pas dans le tas");
		fprintf(stderr, "on ajoute %d au tas\n", numvoisin);

		if (traite[numvoisin] == false)
		{
			//ajouter le voisin au tas
			minHeapInsert(tas, noeudVoisin);
			//on definit le noeud courant en tant que precedent du voisin
			prec[numvoisin] = cour.num;
		}
	}
	puts("");
}

/**
 * @brief Calcule la distance de manhattan
 * 
 * @param courx abscisse du noeud courant
 * @param coury ordonnee du noeud courant
 * @param ciblex abscisse du noeud cible
 * @param cibley ordonnee du noeud cible
 * @return float distance de manhattan
 */
float manhattan(int courx, int coury, int ciblex, int cibley)
{
	return abs(courx - ciblex) + abs(coury - cibley);
}

/**
 * @brief Calcule la distance de Tchebytchev
 * 
 * @param courx abscisse du noeud courant
 * @param coury ordonnee du noeud courant
 * @param ciblex abscisse du noeud cible
 * @param cibley ordonnee du noeud cible
 * @return float distance
 */
float tchebychev(int courx, int coury, int ciblex, int cibley) {
	int x, y;
	
	x = abs(courx - ciblex);
	y = abs(coury - cibley);
	return (x < y) ? y : x;
}

/**
 * @brief Calcule la distance euclidienne
 * 
 * @param courx abscisse du noeud courant
 * @param coury ordonnee du noeud courant
 * @param ciblex abscisse du noeud cible
 * @param cibley ordonnee du noeud cible
 * @return float distance
 */
float euclide(int courx, int coury, int ciblex, int cibley) {
	int x, y;

	x = courx - ciblex;
	y = coury - cibley;
	return sqrt(x * x + y * y);
}

/**
 * @brief Applique l'algorithme A* sur un graphe
 * 
 * @param graphe Le graphe 
 * @param source Le point (noeud) de depart
 * @param cible Le point (noeud) d'arrivee
 * @param chemin Le chemin trouve a la fin de A*
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @return bool_t True si reussi, false sinon
 */
bool_t astar(couples_graphe_t graphe, int source, int cible, liste_t *chemin, int n, int m)
{
	binary_heap_t tas;
	bool_t found = false, *traite;
	node_t cour;
	maillon_t *maillon;
	int *prec, i, u;

	printf("cible %d\n", cible);
	//initialisation
	tas.array = malloc(sizeof(int) * n * m);
	prec = malloc(sizeof(int) * n * m);
	*chemin = initialisation_liste();
	traite = malloc(sizeof(int) * n * m);
	if (tas.array == NULL || prec == NULL || traite == NULL)
	{
		fputs("erreur malloc dijkstra\n", stderr);
		return false;
	}
	for (i = 0; i < n * m; ++i)
	{
		prec[i] = -1;
		traite[i] = false;
	}
	tas.length = n * m;
	tas.heapSize = 0;

	//on insert d'abord la source
	cour.num = source;
	cour.dist = 0;
	cour.distcible = manhattan(source % n, source / n, cible % n, cible / n);
	cour.distsource = 0;
	minHeapInsert(&tas, cour);

	while (found == false && tas.heapSize > 0)
	{

		//on prend le premier de la file d'attente
		cour = heapExtractMin(&tas);
		fprintf(stderr, "on passe a %d de distance %f\n", cour.num, cour.dist);
		//printHeap(tas);
		if (cour.num == -1)
		{
			puts("erreur");
			free(traite);
			free(prec);
			free(tas.array);
			return false;
		}
		traite[cour.num] = true;
		//on n'a pas atteint la cible
		if (cour.num != cible)
		{
			puts("cible non atteinte\n");

			//pour tous les voisins du noeud courant
			for (i = 0; i < graphe.nbAretes; ++i)
			{
				//fprintf(stderr, "on check si %d est dans %d -> %d\n", cour.num, graphe.aretes[i].noeudDeb, graphe.aretes[i].noeudFin);
				if (graphe.aretes[i].noeudDeb == cour.num)
				{
					puts("debut");
					checkVoisinAstar(graphe.aretes[i].noeudFin, cour, graphe.aretes[i], prec, traite, &tas, cible, n);
				}
				else if (graphe.aretes[i].noeudFin == cour.num)
				{
					puts("fin");
					checkVoisinAstar(graphe.aretes[i].noeudDeb, cour, graphe.aretes[i], prec, traite, &tas, cible, n);
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
	for (i = 0; i < n * m; ++i)
	{
		printf("prec[%d] = %d\n", i, prec[i]);
	}
	if ((prec[u] != -1 || u == source))
	{
		while (prec[u] != -1)
		{
			//on ajoute le numero courant
			//chemin[k] = prec[u];
			printf("u : %d, prec[u] = %d\n", u, prec[u]);
			maillon = creerMaillon(prec[u]);
			ajout_lch(chemin, maillon);
			u = prec[u];
			//++k;
		}
	}
	else
	{
		fputs("cible pas trouvee\n", stderr);
	}

	free(traite);
	free(prec);
	free(tas.array);
	return found;
}

/**
 * @brief Effectue un parcours en profondeur sur un graphe (avec affichage au fur et a mesure)
 * 
 * @param graph Le graphe
 * @param debut Point de depart du parcours
 * @param renderer Le rendu
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @param tile Rectangle representant une case du labyrinthe
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param texture La texture pour les sols et les murs
 * @param grille La grille representant le labyrinthe
 * @param destPerso Le rectangle pour le personnage
 * @param perso La texture a appliquer au personnage
 * @param delai Le delai pour afficher chaque etape du parcours
 */
void parcoursEnProfondeur(couples_graphe_t graph, int debut, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso, int delai)
{
	bool_t *marques;

	marques = (bool_t *)malloc(sizeof(bool_t) * graph.nbNoeuds);
	if (marques)
	{
		initialiserMarque(marques, graph.nbNoeuds);
		explorer(graph, debut, marques, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso, delai);
	}
	else
	{
		fprintf(stderr, "Erreur malloc\n");
	}
}

/**
 * @brief Initialise un tableau de marque a false
 * 
 * @param marques Tableau de booleens
 * @param n Taille du tableau
 */
void initialiserMarque(bool_t *marques, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		marques[i] = false;
	}
}

/**
 * @brief Permet d'explorer les fils d'un noeud pour le parcours en profondeur
 * 
 * @param graph Le graphe
 * @param s Noeud de depart
 * @param marques Tableau de booleens
 * @param renderer Le rendu
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @param tile Rectangle representant une case du labyrinthe
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param texture La texture pour les sols et les murs
 * @param grille La grille representant le labyrinthe
 * @param destPerso Le rectangle pour le personnage
 * @param perso La texture a appliquer au personnage
 * @param delai Le delai pour afficher chaque etape du parcours
 */
void explorer(couples_graphe_t graph, int s, bool_t *marques, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso, int delai)
{
	int *voisins,
		nbVoisins,
		i;

	marques[s] = true;

	//affichage
	destPerso.x = positionLab.x + tile.w * (s - (s / n) * m) + tile.w * 0.1;
	destPerso.y = positionLab.y + tile.h * (s / n) + tile.h * 0.1;
	drawAll(marques, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	SDL_Delay(delai);

	voisins = trouverVoisins(graph, s, &nbVoisins);
	for (i = 0; i < nbVoisins; i++)
	{
		if (marques[voisins[i]] == false)
		{
			explorer(graph, voisins[i], marques, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso, delai);

			destPerso.x = positionLab.x + tile.w * (s - (s / n) * m) + tile.w * 0.1;
			destPerso.y = positionLab.y + tile.h * (s / n) + tile.h * 0.1;
			drawAll(marques, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso);
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			SDL_Delay(delai);
		}
	}
}

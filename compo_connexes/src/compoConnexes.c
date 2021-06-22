#include "compoConnexes.h"
#include <stdlib.h>
#include <time.h>

void afficherGraphe(graphe_t graphe, int n) {
	drawAdjencyMatrixGraph(graphe, n, "graphe");
}

void afficherMatriceAdjacence(graphe_t matrix, int n) {
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", matrix[i*n+j]);
		}
		printf("\n");
	}
}

graphe_t createAdjencyMatrix(int n) {
	graphe_t matrix = NULL;
	srand(time(NULL));
	matrix = (int*)malloc(n*n*sizeof(int));
	if (matrix != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				matrix[n*i + j] = rand()%2;
				matrix[n*j + i] = 0/*matrix[n*i + j]*/;
			}
			matrix[n*i + i] = 0;
		}
	}
	else
	{
		puts("Error: memory allocation\n");
	}
	return matrix;
}

partition_t grapheToPartition(graphe_t graphe, int n) {
	partition_t partition;
	int i = 0, j = 0;

	partition = creer(n);
	if(partition.foret == NULL || partition.hauteur == NULL) {
		fputs("erreur conversion du graphe en partition\n", stderr);
		return partition;
	}
	for(i = 0; i < n; ++i) {
		for(j = i + 1; j < n; ++j) {
			if(graphe[i * n + j] == 1) {
				fusion(partition, i, j);
			}
		}
	}
	return partition;
}

element_t** noeudsCompoConnexes(graphe_t graphe, int n) {
	partition_t partition;
	element_t **noeud;
	classe_t *classe;
	int i = 0, j;

	partition = grapheToPartition(graphe, n);
	classe = (element_t *)lister_partition(partition, n);
	while(i < n && classe[i] > -1) {
		++i;
	}
	noeud = malloc(sizeof(element_t *) * i);
	if(noeud == NULL) {
		fputs("erreur allocation de memoire noeudcompoconnexe\n", stderr);
		return NULL;
	}
	for(j = 0; j < i; ++j) {
		noeud[j] = lister_classe(partition, classe[j], n);
	}
	free(classe);
	detruirePartition(partition);
	return noeud;
}
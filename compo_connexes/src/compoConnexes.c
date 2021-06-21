#include "compoConnexes.h"

void genererMatriceAdjacence(graphe_t *graphe, int n) {
	int i, j;

	srand(time(0));
	graphe = malloc(sizeof(int) * n * n);
	if(graphe == NULL) {
		return;
	}

	for(i = 0; i < n; ++i) {
		for(j = i; j < n; ++j) {
			(*graphe)[n * i][j] = rand() % 2;
		}
	}
}

void afficherMatriceAdjacence(graphe_t graphe, int n) {
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", graphe[i][j]);
		}
		printf("\n");
	}
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
			if(graphe[i][j] == 1) {
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

int main(int argc, char const *argv[])
{
	graphe_t graph;
	int n = 10;
	genererMatriceAdjacence(&graph, n);
	afficherMatriceAdjacence(graph, n);
	return 0;
}

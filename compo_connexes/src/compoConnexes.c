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

int main(int argc, char const *argv[])
{
	graphe_t graph;
	int n = 10;
	genererMatriceAdjacence(&graph, n);
	afficherMatriceAdjacence(graph, n);
	return 0;
}

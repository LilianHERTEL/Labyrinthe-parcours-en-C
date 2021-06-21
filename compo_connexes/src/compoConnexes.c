#include "compoConnexes.h"

void genererMatriceAdjacence(graphe_t *graphe, int n) {
	int i, j;

	srand(time(0));
	graphe = malloc(sizeof(int) * n * n);
	if(graphe == NULL) {
		return NULL;
	}

	for(i = 0; i < n; ++i) {
		for(j = i; j < n; ++j) {
			graphe[n * i + j] = rand() % 2;
		}
	}
	return graphe;
}

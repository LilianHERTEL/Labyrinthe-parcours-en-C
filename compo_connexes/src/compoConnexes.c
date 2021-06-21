#include "compoConnexes.h"

void genererMatriceAdjacence(graphe_t *graphe) {
	int i, j;

	srand(time(0));
	graphe = malloc(sizeof(int) * N * N);
	if(graphe == NULL) {
		return NULL;
	}

	for(i = 0; i < N; ++i) {
		for(j = i; j < N; ++j) {
			graphe[N * i + j] = rand() % 2;
		}
	}
	return graphe;
}

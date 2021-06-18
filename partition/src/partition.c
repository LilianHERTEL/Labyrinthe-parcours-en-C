#include "partition.h"

partition_t creer(ensemble_t ensemble) {
	partition_t partition;
	int i;
	
	for(i = 0; i < (int) ensemble; ++i) {
		partition.foret[i] = i;
		partition.hauteur[i] = 1;
	}
	return partition;
}

classe_t recuperer_classe(partition_t partition, element_t element) {
	return partition.foret[(int) element];
}

partition_t fusion(partition_t partition, classe_t x, classe_t y) {
	int i;
	classe_t oldclasse = x, newclasse = y;
	
	if(partition.hauteur[(int) y] < partition.hauteur[(int) x]) {
		oldclasse = y;
		newclasse = x;
	}
	for(i = 0; i < N; ++i) {
		if(partition.foret[i] == oldclasse) {
			partition.foret[i] = newclasse;
		}
	}
	return partition;
}

element_t* lister_classe(partition_t partition, label_t label) {
	int i, k = 0;;
	element_t *liste;
	
	liste = malloc(sizeof(element_t) * N);
	if(liste == NULL) {
		return NULL;
	}
	
	for(i = 0; i < N; ++i) {
		if((int) partition.foret[i] == (int) label) {
			liste[k] = (element_t) i;
			++k;
		}
	}
	if(k < N) {
		liste[k] = -1;
	}
	return liste;
}
classe_t* lister_partition(partition_t partition);

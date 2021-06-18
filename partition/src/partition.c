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
		if(partition.foret[i] == (int) oldclasse) {
			partition.foret[i] = (int) newclasse;
		}
	}
	return partition;
}

element_t* lister_classe(partition_t partition, label_t label);
classe_t* lister_partition(partition_t partition);

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

classe_t recuperer_classe(element_t element);
partition_t fusion(element_t x, element_t y);
element_t* lister_classe(label_t label, partition_t);
classe_t* lister_partition(partition_t partition);


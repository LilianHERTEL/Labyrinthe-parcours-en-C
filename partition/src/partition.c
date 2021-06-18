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

#include <stdio.h>
partition_t fusion(partition_t partition, element_t x, element_t y) {
	int i;
	classe_t oldclasse, newclasse, classex, classey, min;
	
	fprintf(stderr, "fusionner(%d,%d)\n", (int) x, (int) y);
	classex = recuperer_classe(partition, x);
	classey = recuperer_classe(partition, y);
	oldclasse = classex;
	newclasse = classey;
	if(partition.hauteur[(int) classey] == partition.hauteur[(int) classex]) {
		++(partition.hauteur[classex]);
	}
	if(partition.hauteur[(int) classey] < partition.hauteur[(int) classex]) {
		oldclasse = classey;
		newclasse = classex;
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

classe_t* lister_partition(partition_t partition) {
	int i, k;
	classe_t *liste;
	
	liste = malloc(sizeof(classe_t) * N);
	if(liste == NULL) {
		return NULL;
	}
	
	for(i = 0; i < N; ++i) {
		if((int) partition.foret[i] == i) {
			liste[k] = (classe_t) liste[i];
			++k;
		}
	}
	if(k < N) {
		liste[k] = -1;
	}
	return liste;
}

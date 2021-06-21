#include "partition.h"

partition_t creer(ensemble_t ensemble) {
	partition_t partition;
	int i;
	
	partition.foret = malloc(sizeof(classe_t) * ensemble);
	partition.hauteur = malloc(sizeof(int) * ensemble);
	if(partition.hauteur == NULL || partition.foret == NULL) {
		return partition;
	}

	for(i = 0; i < (int) ensemble; ++i) {
		partition.foret[i] = i;
		partition.hauteur[i] = 1;
	}
	return partition;
}

classe_t recuperer_classe(partition_t partition, element_t element) {
	return partition.foret[(int) element];
}

partition_t fusion(partition_t partition, element_t x, element_t y) {
	classe_t classex, classey, min;
	
	classex = recuperer_classe(partition, x);
	classey = recuperer_classe(partition, y);
	if(partition.hauteur[(int) classey] == partition.hauteur[(int) classex]) {
		min = (classex <= classey) ? classex : classey;
		++(partition.hauteur[min]);
	}
	if(partition.hauteur[(int) classey] < partition.hauteur[(int) classex]) {
		partition.foret[(int) y] = classex;
		partition.foret[(int) classey] = classex;
	}
	else {
		partition.foret[(int) x] = classey;
		partition.foret[(int) classex] = classey;
	}
	return partition;
}

element_t* lister_classe(partition_t partition, label_t label, int n) {
	int i, k = 0;
	element_t *liste;
	
	liste = malloc(sizeof(element_t) * n);
	if(liste == NULL) {
		return NULL;
	}
	
	for(i = 0; i < n; ++i) {
		if((int) partition.foret[i] == (int) label) {
			liste[k] = (element_t) i;
			++k;
		}
	}
	if(k < n) {
		liste[k] = -1;
	}
	return liste;
}

void detruirePartition(partition_t partition) {
	free(partition.foret);
	free(partition.hauteur);
}

classe_t* lister_partition(partition_t partition, int n) {
	int i, k = 0;
	classe_t *liste;
	
	liste = malloc(sizeof(classe_t) * n);
	if(liste == NULL) {
		return NULL;
	}

	for(i = 0; i < n; ++i) {
		if((int) partition.foret[i] == i) {
			liste[k] = (classe_t) partition.foret[i];
			++k;
		}
	}
	if(k < n) {
		liste[k] = -1;
	}
	return liste;
}

void afficherClasse(classe_t *classe) {
        int i = 0, n = 11;

        while(i < n && classe[i] != -1) {
                printf("%d ", classe[i]);
                ++i;
        }
        puts("");
}

void afficherForet(partition_t partition) {
        int i, n = 11;

        for(i = 0; i < n; ++i) {
                printf("indice[%d] : %d (hauteur %d)\n", i, partition.foret[i], partition.hauteur[i]);
        }
        puts("");
}

classe_t classeMere(element_t element, partition_t partition) {
	while(partition.foret[element] != element) {
		element = partition.foret[element];
	}
	return element;
}

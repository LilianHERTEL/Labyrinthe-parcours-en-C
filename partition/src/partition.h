#pragma once

#define N 5

typedef int ensemble_t;
typedef int classe_t;
typedef partition_t {
	int foret[N],
	int hauteur[N]
};
typedef int element_t;
typedef int label_t;

partition_t creer(ensemble_t ensemble);
classe_t recuperer_classe(element_t element);
partition_t fusion(element_t x, element_t y);
element_t* lister_classe(label_t label, partition_t);
classe_t* lister_partition(partition_t partition);


#pragma once

#include <stdlib.h>

#define N 5

typedef int ensemble_t;
typedef int classe_t;
typedef int element_t;
typedef int label_t;
typedef struct {
	classe_t foret[N];
	int hauteur[N];
} partition_t;

partition_t creer(ensemble_t ensemble);
classe_t recuperer_classe(partition_t partition, element_t element);
partition_t fusion(partition_t partition, classe_t x, classe_t y);
element_t* lister_classe(partition_t partition, label_t label);
classe_t* lister_partition(partition_t partition);


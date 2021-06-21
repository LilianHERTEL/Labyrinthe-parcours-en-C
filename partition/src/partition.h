#pragma once

#include <stdlib.h>

//#define N 11

typedef int ensemble_t;
typedef int classe_t;
typedef int element_t;
typedef int label_t;
typedef struct {
	classe_t *foret;
	int *hauteur;
} partition_t;

partition_t creer(ensemble_t n);
classe_t recuperer_classe(partition_t partition, element_t element);
partition_t fusion(partition_t partition, element_t x, element_t y);
element_t* lister_classe(partition_t partition, label_t labeli, int n);
classe_t* lister_partition(partition_t partition, int n);
void detruirePartition(partition_t *partition);

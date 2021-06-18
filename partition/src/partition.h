#pragma once
#include "arbre.h"

#define N 5

typedef ensemble_t;
typedef classe_t;
typedef partition_t;
typedef element_t;
typedef label_t;

partition_t creer(ensemble_t ensemble);
classe_t recuperer_classe(element_t element);
partition_t fusion(element_t x, element_t y);
element_t* lister_classe(label_t label, partition_t);
classe_t* lister_partition(partition_t partition);


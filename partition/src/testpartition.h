#pragma once

#include <stdio.h>
#include "partition.h"

typedef enum {false, true} bool;

bool testCreer();
bool testRecupererClasse();
bool testFusion();
bool testListerClasse();
bool testListerPartition();
void afficherForet(partition_t partition);
void afficherClasse(classe_t *classe);

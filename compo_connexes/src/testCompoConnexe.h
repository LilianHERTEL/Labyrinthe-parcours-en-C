#pragma once

#include <stdio.h>
#include "compoConnexes.h"
#include "grapheListeAretes.h"
#include "graphviz.h"

typedef enum {false, true} bool;

bool testCreateAdjencyMatrix();
bool testGrapheToPartition();
bool testNoeudsCompoConnexes();

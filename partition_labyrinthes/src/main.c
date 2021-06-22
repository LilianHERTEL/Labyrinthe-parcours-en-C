#include <stdio.h>
#include "grapheListeAretes.h"

int main(void)
{
    int n = 10;
    couples_graphe_t graph;
    genererGraphe(&graph, n);
    printAretes(graph);
    fisherYate(&graph);
    printAretes(graph);
    return 0;
}
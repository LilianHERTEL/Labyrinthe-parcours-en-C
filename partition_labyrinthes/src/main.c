#include <stdio.h>
#include "grapheListeAretes.h"
#include "graphviz.h"
#include "labyrinthe_arbo.h"


int main(void)
{
    int n = 10;
    couples_graphe_t graph;
    genererGrapheLabyrinthe(&graph, n);
    printAretes(graph);
    fisherYate(&graph);
    printAretes(graph);
    drawCouplesGraph(graph, "labyrinthe_arbo", NULL, 0);

    return 0;
}

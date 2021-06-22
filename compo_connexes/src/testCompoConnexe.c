#include "testCompoConnexe.h"

int main(void)
{
        int n = 10;
        graphe_t matrix;
        couples_graphe_t graph;
        partition_t partition;
	element_t **element;
	int noeudsI;

        genererGraphe(&graph, n);
        drawCouplesGraph(graph, "exempleCouplesGraphe");

        matrix = createAdjencyMatrix(n);
        afficherMatriceAdjacence(matrix, n);
        drawAdjencyMatrixGraph(matrix, n, "exempleMatAdjacence");
	partition = grapheToPartition(matrix, n);
	afficherForet(partition, n);
	element = noeudsCompoConnexes(matrix, n, &noeudsI);
        afficherNoeudsCompoConnexes(element, n, noeudsI);	
        return 0;
}
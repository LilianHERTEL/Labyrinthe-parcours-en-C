#include "testCompoConnexe.h"

int main(void)
{
	(testCreateAdjencyMatrix() && testGrapheToPartition()) ? puts("tests OK") : puts("echec tests");
	return 0;
}

bool testCreateAdjencyMatrix() {
	graphe_t matrix = NULL;
        int n = 10;

	matrix = createAdjencyMatrix(n);
	if(matrix == NULL) {
		fputs("erreur creation matrice adjacente\n", stderr);
		return false;
	}
	free(matrix);
	return true;
}

bool testGrapheToPartition() {
	graphe_t matrix = NULL;
	partition_t partition;
	int n = 3;
	char c = 0;

	matrix = createAdjencyMatrix(n);
        if(matrix == NULL) {
                fputs("erreur creation de la matrice avant test dans grapheToPartition\n", stderr);
                return false;
        }
	partition = grapheToPartition(matrix, n);
	afficherGraphe(matrix, n);
	afficherForet(partition, n);
	puts("validation manuelle : y/n");
	fscanf(stdin, "%c%*c", &c);
	free(matrix);
        detruirePartition(partition);
	if(c == 'y' || c == 'Y') {
		return true;
	}
	fputs("graphe non conforme\n", stderr);
	return false;

}

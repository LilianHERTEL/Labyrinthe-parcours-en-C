#include "compoConnexes.h"
#include <stdlib.h>
#include <time.h>

void afficherMatriceAdjacence(graphe_t matrix, int n) {
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", matrix[i*n+j]);
		}
		printf("\n");
	}
}

graphe_t createAdjencyMatrix(int n) {
	graphe_t matrix = NULL;
	srand(time(NULL));
	matrix = (int*)malloc(n*n*sizeof(int));
	if (matrix != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				matrix[n*i + j] = rand()%2;
				matrix[n*j + i] = matrix[n*i + j];
			}
			matrix[n*i + i] = 0;
		}
	}
	else
	{
		puts("Error: memory allocation\n");
	}
	return matrix;
}

int main(void)
{
	int n = 10;
	graphe_t matrix;
	
	matrix = createAdjencyMatrix(n);
	afficherMatriceAdjacence(matrix, n);
	drawAdjencyMatrixGraph(matrix, n, "exempleMatAdjacence");

	return 0;
}
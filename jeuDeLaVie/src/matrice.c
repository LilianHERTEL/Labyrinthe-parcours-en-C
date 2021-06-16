#include "matrice.h"

void freeGrid(int ** grid, int n)
{
    int     i;

    for(i=0; i < n; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

int ** allocGrid(int n, int m)
{
   int  ** grid,
            i = 0;

    grid = malloc(n * sizeof(int *));

    if(grid)
    {	
        do {
            grid[i] = (int *)malloc(m * sizeof(int));
	        i++;
        } while(i < n && grid[i-1] != NULL);

        if(grid[i-1] == NULL)
        {
            freeGrid(grid, i-1);
            grid = NULL;
        }
    } 
    return grid;
}

int ** createGrid(int ** grid, int n, int m)
{
    int i,
          j;
    
    srand (time (NULL));
    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            grid[i][j] = rand() % 2;
        }
    }
    return grid;
}

void displayGrid(int ** grid, int n, int m)
{
    int i,
          j;
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}
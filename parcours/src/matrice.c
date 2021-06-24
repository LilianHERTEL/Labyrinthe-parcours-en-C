#include "matrice.h"

/**
 * @brief Libere une matrice d'entiers
 * 
 * @param grid matrice d'entier
 * @param n nombre de lignes de la matrice
 */
void freeGrid(int **grid, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

/**
 * @brief Alloue l'espace pour une matrice d'entiers de taille n*m
 * 
 * @param n nombre de lignes
 * @param m nombre de colonnes
 * @return int** 
 */
int **allocGrid(int n, int m)
{
    int **grid,
        i = 0;

    grid = malloc(n * sizeof(int *));

    if (grid)
    {
        do
        {
            grid[i] = (int *)malloc(m * sizeof(int));
            i++;
        } while (i < n && grid[i - 1] != NULL);

        if (grid[i - 1] == NULL)
        {
            freeGrid(grid, i - 1);
            grid = NULL;
        }
    }
    setToZero(grid, n, m);
    return grid;
}

/**
 * @brief Affiche la matrice dans le terminal
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 */
void displayGrid(int **grid, int n, int m)
{
    int i,
        j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void setToZero(int **grid, int n, int m)
{
    int i,
        j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            grid[i][j] = 15;
        }
    }
}

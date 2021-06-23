#include <stdio.h>
#include "binary_heap.h"
#include "bool.h"
#include <stdlib.h>

/**
 * @brief Retourne l'indice du parent de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getParent(int index)
{
    return index / 2;
}

/**
 * @brief Retourne l'indice du fils de gauche de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getLeftChild(int index)
{
    return 2 * index;
}

/**
 * @brief Retourne l'indice du fils de droite de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getRightChild(int index)
{
    return 2 * index + 1;
}

/**
 * @brief Affiche le tableau du tas binaire dans le terminal 
 * 
 * @param heap Le tas binaire
 */
void printHeap(binary_heap_t heap)
{
    int i;
    printf("heap size = %d\n", heap.length);
    for (i = 1; i <= heap.length; i++)
    {
        printf("numero : %d distance : %f\n", heap.array[i].num, heap.array[i].dist);
    }
    printf("\n");
}

/**
 * @brief Permet de deplacer une valeur a la bonne place dans le tas
 * 
 * @param heap Le tas binaire
 * @param val Indice de la valeur a deplacer
 */
void minHeapify(binary_heap_t *heap, int val)
{
    int left,
        right,
        min;

    left = getLeftChild(val);
    right = getRightChild(val);

    if (left <= heap->heapSize && heap->array[left] < heap->array[val])
    {
        min = left;
    }
    else
    {
        min = val;
    }
    if (right <= heap->heapSize && heap->array[right] < heap->array[min])
    {
        min = right;
    }
    if (min != val)
    {
        permute(heap->array, val, min);
        minHeapify(heap, min);
    }
}

/**
 * @brief Construit un tas binaire minimum a partir d'un tas binaire quelconque
 * 
 * @param heap Tas binaire quelconque
 */
void buildMinHeap(binary_heap_t *heap)
{
    int i;

    heap->heapSize = heap->length;
    for (i = (heap->length / 2); i > 0; i--)
    {
        minHeapify(heap, i);
    }
}

/**
 * @brief Permute 2 valeurs d'indices i et j dans la tableau array
 * 
 * @param array Tableau de valeurs
 * @param i Indice du premier element
 * @param j Indice du deuxieme element
 */
void permute(int array[], int i, int j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

/**
 * @brief Tri par tas du tableau
 * 
 * @param heap Le tas binaire à trier
 */
void heapSort(binary_heap_t *heap)
{
    buildMinHeap(heap);
    for (int i = heap->length; i > 1; i--)
    {
        permute(heap->array, 1, i);
        (heap->heapSize)--;
        minHeapify(heap, 1);
    }
}

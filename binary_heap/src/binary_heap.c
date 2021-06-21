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
int getParent(int index) {
    return index/2;
}

/**
 * @brief Retourne l'indice du fils de gauche de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getLeftChild(int index) {
    return 2*index;
}

/**
 * @brief Retourne l'indice du fils de droite de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getRightChild(int index) {
    return 2*index + 1;
}

/**
 * @brief Affiche le tableau du tas binaire dans le terminal 
 * 
 * @param heap Le tas binaire
 */
void printHeap(binary_heap_t* heap) {
    int i;
    printf("heap size = %d\n", heap->length);
    for (i = 1; i <= heap->length; i++)
    {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}
/*
bool_t heapInsert(binary_heap_t* heap, int val) {
    bool_t status = false;
    int index, parent;
    index = heap->heapSize;
    if (index < heap->length)
    {
        heap->array[index] = val;
        heap->heapSize++;
        parent = getParent(index);
        while (heap->array[index] < heap->array[parent] && index != 1)
        {
            permute(heap->array, parent, index);
            index = parent;
            parent = getParent(index);
        }
        status = true;
    }
    return status;
}
*/

/**
 * @brief Permet de deplacer une valeur a la bonne place dans le tas
 * 
 * @param heap Le tas binaire
 * @param val Indice de la valeur a deplacer
 */
void minHeapify(binary_heap_t * heap, int val)
{
    int left,
        right,
        min;
    
    left = getLeftChild(val);
    right = getRightChild(val);

    if(left <= heap->heapSize && heap->array[left] < heap->array[val])
    {
        min = left;
    }
    else
    {
        min = val;
    }
    if(right <= heap->heapSize && heap->array[right] < heap->array[min])
    {
        min = right;
    }
    if(min != val)
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
void buildMinHeap(binary_heap_t * heap)
{
    int i;

    heap->heapSize = heap->length;
    for(i = (heap->length / 2); i > 0; i--)
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
void permute(int array[], int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

/*
void createHeap(int source_array[], int size, binary_heap_t* heap) {
    int i;
    heap->heapSize = 1;
    heap->length = MAX;
    for (i = 0; i < size; i++)
    {
        heapInsert(heap, source_array[i]);
        printf("Val = %d\n", source_array[i]);
    }
}*/

void heapSort(binary_heap_t* heap) {
    buildMinHeap(heap);
    for (int i = heap->length; i > 1; i--)
    {
        permute(heap->array, 1, i);
        (heap->heapSize)--;
        minHeapify(heap, 1);
    }
}
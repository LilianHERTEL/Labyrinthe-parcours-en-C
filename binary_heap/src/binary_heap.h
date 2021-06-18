#pragma once
#include <stdio.h>
#include "bool.h"

#define MAX 10

typedef struct binary_heap 
{
    int length;
    int heapSize;
    int array[MAX];
} binary_heap_t;

int getParent(int index);
int getLeftChild(int index);
int getRightChild(int index);

void printHeap(binary_heap_t heap);
bool_t heapInsert(binary_heap_t* heap, int val);
void permute(int array[], int i, int j);

/**
 * @brief Permet de deplacer une valeur a la bonne place dans le tas
 * 
 * @param heap Le tas binaire
 * @param val Indice de la valeur a deplacer
 */
void minHeapify(binary_heap_t * heap, int val);

/**
 * @brief Construit un tas binaire minimum a partir d'un tas binaire quelconque
 * 
 * @param heap Tas binaire quelconque
 */
void buildMinHeap(binary_heap_t * heap);

void createHeap(int source_array[], int size, binary_heap_t* heap);
//void minHeapify(int array[], int index);
//void buildMinHeap(binary_heap_t* heap);
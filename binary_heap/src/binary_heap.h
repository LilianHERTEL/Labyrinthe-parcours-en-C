#pragma once
#include <stdio.h>
#include "bool.h"

#define MAX 100

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
void createHeap(int source_array[], int size, binary_heap_t* heap);
//void minHeapify(int array[], int index);
//void buildMinHeap(binary_heap_t* heap);
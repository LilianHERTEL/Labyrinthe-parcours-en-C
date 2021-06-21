#include "testbinary_heap.h"

void test_MinHeapify()
{
    binary_heap_t heap;
    int tab[3] = {2, 3, 1};
    heap.heapSize = 3;
    heap.length = 3;
    for(int i = 1; i<= 3; i++)
        heap.array[i] = tab[i-1];

    printf("Test avec l'indice 0\n");
    printHeap(heap);
    minHeapify(&heap, 0);
    printHeap(heap);

}
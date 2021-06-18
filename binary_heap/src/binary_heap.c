#include <stdio.h>
#include "binary_heap.h"
#include "bool.h"

int getParent(int index) {
    return index/2;
}

int getLeftChild(int index) {
    return 2*index;
}

int getRightChild(int index) {
    return 2*index + 1;
}

void printHeap(binary_heap_t heap) {
    int i;
    printf("heap size = %d\n", heap.heapSize);
    for (i = 1; i < heap.heapSize; i++)
    {
        printf("%d ", heap.array[i]);
    }
    printf("\n");
}

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

void permute(int array[], int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void createHeap(int source_array[], int size, binary_heap_t* heap) {
    int i;
    heap->heapSize = 1;
    heap->length = MAX;
    for (i = 0; i < size; i++)
    {
        heapInsert(heap, source_array[i]);
        printf("Val = %d\n", source_array[i]);
    }
}

int main(void)
{
    binary_heap_t heap;
    heap.heapSize = 1;
    heap.length = MAX;
    bool_t status;
    //int tab[] = {41, 87, 14, 23, 90, 50, 64, 53, 5, 32};
    //int tab_size = 10;
    
    status = heapInsert(&heap, 41);
    status = heapInsert(&heap, 87);
    status = heapInsert(&heap, 14);
    status = heapInsert(&heap, 23);
    status = heapInsert(&heap, 90);
    status = heapInsert(&heap, 50);
    status = heapInsert(&heap, 64);
    status = heapInsert(&heap, 53);
    status = heapInsert(&heap, 5);
    status = heapInsert(&heap, 32);
    
    //createHeap(tab, tab_size, &heap);
    
    printHeap(heap);
    return 0;
}

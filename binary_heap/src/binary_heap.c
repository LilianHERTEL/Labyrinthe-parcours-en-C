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

int main(int argc, char const *argv[])
{
    binary_heap_t heap;
    heap.heapSize = 1;
    heap.length = MAX;
    bool_t status;
    status = heapInsert(&heap, 16);
    status = heapInsert(&heap, 14);
    status = heapInsert(&heap, 10);
    status = heapInsert(&heap, 8);
    status = heapInsert(&heap, 7);
    status = heapInsert(&heap, 9);
    status = heapInsert(&heap, 3);
    status = heapInsert(&heap, 2);
    status = heapInsert(&heap, 4);
    status = heapInsert(&heap, 1);
    printHeap(heap);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_heap.h"

#define SIZE 10000

int cmpfunc (const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}

void callQSort(int* arrayQSort) {
    qsort(arrayQSort, SIZE, sizeof(int), cmpfunc);
}

/*int main(int argc, char const *argv[])
{
    int i;
    time_t t;
    binary_heap_t heap;
    clock_t beforeHeapSort, afterHeapSort, beforeQSort, afterQSort;
    int arrayQSort[SIZE];
    heap.length = SIZE;
    heap.heapSize = heap.length;
    heap.array = (int*) malloc(sizeof(int)*(heap.length+1));
    printf("%d\n", heap.length);
    printf("%d\n", heap.heapSize);
    if (heap.array == NULL)
    {
        printf("Error: memory allocation\n");
        exit(EXIT_FAILURE);
    }
    
    srand((unsigned)time(&t));
    for (i = 1 ; i <= SIZE ; i++) {
        heap.array[i] = rand() % SIZE;
        arrayQSort[i-1] = heap.array[i];
    }
    //printHeap(&heap);
    beforeHeapSort = (unsigned)time(&t);
    beforeHeapSort = clock();
    heapSort(&heap);
    afterHeapSort = clock();
    beforeQSort = clock();
    callQSort(arrayQSort);
    afterQSort = clock();

    printf("HEAP SORT TIME : %ld\n", (afterHeapSort -  beforeHeapSort) * 1000 / CLOCKS_PER_SEC);
    printf("QUICK SORT TIME : %ld\n", (afterQSort -  beforeQSort) * 1000 / CLOCKS_PER_SEC);
    //printHeap(&heap);  

    free(heap.array);

    return 0;
}*/

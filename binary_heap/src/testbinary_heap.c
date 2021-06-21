#include "testbinary_heap.h"

void test_MinHeapify()
{
    binary_heap_t heap;
    int           i,
                  tab[3] = {2, 3, 1};

    heap.heapSize = 3;
    heap.length = 3;
    heap.array = (int *)malloc((heap.length + 1) * sizeof(int));

    if(heap.array)
    {
        for(i = 1; i<= heap.length; i++)
            heap.array[i] = tab[i-1];

        puts("Il faut s'assurer que l'indice qu'on choisi est < heapSize avant d'appeler cette fonction\n");

        puts("Test avec l'indice 1");
        puts("Comportement attendu : l'element d'indice 1 (2) doit etre deplace avec l'element de droite (1) car 2>1");
        puts("Tas avant :");
        printHeap(heap);
        minHeapify(&heap, 1);
        puts("Tas apres :");
        printHeap(heap);
        puts("");

        puts("Test avec l'indice 2");
        puts("Comportement attendu : l'element d'indice 2 (3) ne bougera pas car il n'a pas d'elements fils (l'indice 2*2 depasse heapSize)");
        puts("Tas avant :");
        printHeap(heap);
        minHeapify(&heap, 2);
        puts("Tas apres :");
        printHeap(heap);

        free(heap.array);
    }
    else
    {
        fprintf(stderr,"Erreur malloc\n");
    }
}

void testBuildMinHeap()
{
    binary_heap_t heap;
    int           i,
                  tab[4] = {0, 2, 3, 1};
    
    heap.length = 4;
    heap.array = (int *)malloc((heap.length + 1) * sizeof(int));
    if(heap.array)
    {
        heap.heapSize = heap.length;
        for(i = 1; i<= heap.length; i++)
            heap.array[i] = tab[i-1];

        printHeap(heap);
        puts("Le tas devrait etre ");
        buildMinHeap(&heap);
        printHeap(heap);
    
        free(heap.array);
    }
    else
    {
        fprintf(stderr,"Erreur malloc\n");
    }

}
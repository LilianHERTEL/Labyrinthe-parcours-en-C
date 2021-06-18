#pragma once
#include <stdio.h>

typedef struct binary_heap 
{
    int length;
    int heapSize;
    int* array;
} binary_heap_t;

int getParent(int index);
int getLeftChild(int index);
int getRightChild(int index);
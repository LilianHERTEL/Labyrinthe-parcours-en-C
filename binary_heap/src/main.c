#include "testbinary_heap.h"
#include "comparison.h"


int main()
{
    //test_MinHeapify();
    testBuildMinHeap();

    comparison(100000);

    return 0;
}
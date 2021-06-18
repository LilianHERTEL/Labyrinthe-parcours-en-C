#include <stdio.h>

int getParent(int index) {
    return index/2;
}

int getLeftChild(int index) {
    return 2*index;
}

int getRightChild(int index) {
    return 2*index + 1;
}
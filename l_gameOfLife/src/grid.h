#pragma once
#include <stdio.h>

typedef struct grid {
    bool **grid;
	int x;
	int y;
} grid_t;

grid_t createGrid(int x, int y);
void initializeBlankGrid(grid_t grid);
void initializeRandomGrid(grid_t grid);
void displayGrid(grid_t grid);
void freeGrid(grid_t grid);
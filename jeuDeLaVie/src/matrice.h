#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void freeGrid(int ** grid, int n);
int ** allocGrid(int n, int m);
int ** createGrid(int ** grid, int n, int m);
void displayGrid(int ** grid, int n, int m);

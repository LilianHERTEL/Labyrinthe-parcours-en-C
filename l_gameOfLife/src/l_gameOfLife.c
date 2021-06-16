#include <SDL2/SDL.h>
#include <stdio.h>
#include "l_gameOfLife.h"
#include "bool.h"

void initLife(rules_t *life) {
	int i;
	
	for(i = 0; i < 9; ++i) {
		switch(i) {
			case 3:
				life->naissance[i] = 1;
				life->survie[i] = 1;
				break;
			case 2:
				life->survie[i] = 1;
				break;
			default:
				life->naissance[i] = 0;
				life->survie[i] = 0;
		}
	}
}

void initMaze(rules_t *maze) {
  int i;
	
	for(i = 0; i < 9; ++i) {
		switch(i) {
			case 0:
				maze->survie[i] = 0;
				maze->naissance[i] = 0;
				break;
			case 5:
				maze->survie[i] = 0;
				maze->naissance[i] = 0;
				break;
			case 3:
				maze->naissance[i] = 1;
				maze->survie[i] = 1;
				break;
			default:
				maze->survie[i] = 1;
				maze->naissance[i] = 0;
		}
	}
}

int main(int argc, char const *argv[]) {
  
  return 0;
}

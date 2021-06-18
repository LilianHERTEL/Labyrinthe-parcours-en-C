#include "testpartition.h"

int main() {
	(testCreer() && testRecupererClasse() && testFusion() && testListerClasse() && testListerPartition()) ? printf("tests ok") : printf("erreur tests");
	return 0;
}

bool testCreer() {
	int i;
	partition_t test;
	bool code = true;

	test = creer(N);
	for(i = 0; i < N; ++i) {
		if(test.foret[i] != i || test.hauteur[i] != 1) {
			code = false;
		}
	}
	return code;
}

bool testRecupererClasse();
bool testFusion();
bool testListerClasse();
bool testListerPartition();

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
			puts("echec creation\n");
		}
	}
	return code;
}

bool testRecupererClasse() {
	partition_t partition;
	
	partition = creer(N);
	if(recuperer_classe(partition, 1) != 1) {
		puts("echec recuperer classe initiale\n");
		return false;
	}
	partition = fusion(partition, 0, 1);
	if(recuperer_classe(partition, 1) != 0) {
		puts("echec recuperer classe apres fusion\n");
		return false;
	}
	return true;
}

bool testFusion();
bool testListerClasse();
bool testListerPartition();

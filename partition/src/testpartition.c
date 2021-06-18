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

bool testFusion() {
	partition_t partition;
	
	partition = creer(N);
	partition = fusion(partition, 0, 1);
	if(recuperer_classe(partition, 1) != 0) {
		puts("echec fusion simple\n");
		return false;
	}
	partition = fusion(partition, 2, 3);
	partition = fusion(partition, 3, 4);
	partition = fusion(partition, 1, 2);
	if(recuperer_classe(partition, 0) != 2) {
		puts("echec fusions combinees\n");
		return false;
	}
	return true;
}

bool testListerClasse() {
	partition_t partition;
	element_t *element;
	
	partition = creer(N);
	partition = fusion(partition, 0, 1);
	element = lister_classe(partition, 0);
	if(element[0] != 0 || element[1] != 1 || element[2] != -1) {
		puts("echec listage classes\n");
		return false;
	}
	return true;
}
bool testListerPartition();

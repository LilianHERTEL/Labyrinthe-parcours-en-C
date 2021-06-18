#include "testpartition.h"

int main() {
	(testCreer() && testRecupererClasse() && testFusion() && testListerClasse() && testListerPartition()) ? puts("tests ok") : puts("erreur tests");
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
	puts("creer OK");
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
		printf("classe de 0 : %d\nclasse de 1 : %d\n", (int) recuperer_classe(partition, 0), (int) recuperer_classe(partition, 1));
		return false;
	}
	puts("recuperer classe OK");
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
	if(recuperer_classe(partition, 4) != 0) {
		puts("echec fusions combinees\n");
		afficherForet(partition);
		return false;
	}
	puts("fusion OK");
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
	puts("liste classe OK");
	return true;
}

bool testListerPartition() {
	partition_t partition;
	classe_t *classe;
	int i;
	
	partition = creer(N);
	for(i = 1; i < N-1; ++i) {
		partition = fusion(partition, 0, i);
	}
	classe = lister_partition(partition);
	if(classe[0] != 0 || classe[1] != N-1) {
		puts("echec listage partition\n");
		return false;
	}
	puts("liste partition OK");
	return true;
}

void afficherForet(partition_t partition) {
	int i;
	
	for(i = 0; i < N; ++i) {
		printf("indice[%d] : %d (hauteur %d)\n", i, partition.foret[i], partition.hauteur[i]);
	}
}

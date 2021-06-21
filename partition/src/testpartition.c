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
	partition = fusion(partition, 10, 3);
	if(recuperer_classe(partition, 10) != 2) {
		puts("echec fusions combinees\n");
		afficherForet(partition);
		return false;
	}
	partition = fusion(partition, 5, 9);
	partition = fusion(partition, 4, 6);
	partition = fusion(partition, 8, 7);
	if(recuperer_classe(partition, 8) != 7) {
		puts("echec fusions combinees\n");
		afficherForet(partition);
		return false;
	}
	partition = fusion(partition, 8, 9);
	if(recuperer_classe(partition, 5) != 5 || recuperer_classe(partition, 7) != 5 || recuperer_classe(partition, 9) != 5) {
		puts("echec fusions combinees\n");
		afficherForet(partition);
		return false;
	}
	partition = fusion(partition, 6, 8);
	if(recuperer_classe(partition, 4) != 5) {
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
		afficherForet(partition);
		puts("echec listage classes\n");
		return false;
	}
	puts("liste classe OK");
	free(element);
	return true;
}

bool testListerPartition() {
	partition_t partition;
	classe_t *classe;
	int i;
	
	partition = creer(N);
	for(i = 1; i < 2 * N / 3; ++i) {
		partition = fusion(partition, 0, i);
	}
	classe = lister_partition(partition);
	if(classe[0] != 0 || classe[N-1] != N-1) {
		afficherForet(partition);
		afficherClasse(classe);
		puts("echec listage partition\n");
		return false;
	}
	puts("liste partition OK");
	free(classe);
	return true;
}

void afficherClasse(classe_t *classe) {
        int i = 0;

        while(i < N && classe[i] != -1) {
                printf("%d ", classe[i]);
                ++i;
        }
        puts("");
}

void afficherForet(partition_t partition) {
	int i;
	
	for(i = 0; i < N; ++i) {
		printf("indice[%d] : %d (hauteur %d)\n", i, partition.foret[i], partition.hauteur[i]);
	}
	puts("");
}

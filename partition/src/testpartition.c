#include "testpartition.h"

int main() {
	(testCreer() && testRecupererClasse() && testFusion() && testListerClasse() && testListerPartition()) ? printf("tests ok") : printf("erreur tests");
	return 0;
}

bool testCreer();
bool testRecupererClasse();
bool testFusion();
bool testListerClasse();
bool testListerPartition();

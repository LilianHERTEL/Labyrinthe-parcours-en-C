#include "testpartition.h"
#include "graphviz.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    (testCreer() && testRecupererClasse() && testFusion() && testListerClasse() && testListerPartition()) && testClasseMere() ? puts("tests ok") : puts("erreur tests");
    //partitionSimple();

    return 0;
}

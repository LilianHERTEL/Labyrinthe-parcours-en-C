#include <stdio.h>
#include "grapheListeAretes.h"
#include "graphviz.h"
#include "labyrinthe_arbo.h"
#include "kruskal.h"
#include "matrice.h"


/*
int main(void)
{
    int n = 10, tailleLabyrintheCouvrant;
    couples_graphe_t graph;
    arete_t* labyrintheCouvrant;
    int** matrice;
    genererGrapheLabyrinthe(&graph, n);
    labyrintheCouvrant = arbreCouvrantPoidsMin(graph, &tailleLabyrintheCouvrant);
    matrice = arbreCouvrantToMatrice(labyrintheCouvrant, tailleLabyrintheCouvrant, n);
    displayGrid(matrice, n, n);
    
    drawCouplesGraph(graph, "labyrinthe_arbo", labyrintheCouvrant, tailleLabyrintheCouvrant);

    return 0;
}*/

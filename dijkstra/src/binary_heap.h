#pragma once
#include <stdio.h>
#include "bool.h"

typedef struct {
	int num;
	float dist;
} node_t;

typedef struct binary_heap 
{
    int   length;
    int   heapSize;
    node_t * array;
} binary_heap_t;

/**
 * @brief Retourne l'indice du parent de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getParent(int index);

/**
 * @brief Retourne l'indice du fils de gauche de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getLeftChild(int index);

/**
 * @brief Retourne l'indice du fils de droite de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getRightChild(int index);

/**
 * @brief Affiche le tableau du tas binaire dans le terminal 
 * 
 * @param heap Le tas binaire
 */
void printHeap(binary_heap_t heap);

/**
 * @brief Permute 2 valeurs d'indices i et j dans la tableau array
 * 
 * @param array Tableau de valeurs
 * @param i Indice du premier element
 * @param j Indice du deuxieme element
 */
void permute(int array[], int i, int j);

/**
 * @brief Permet de deplacer une valeur a la bonne place dans le tas
 * 
 * @param heap Le tas binaire
 * @param val Indice de la valeur a deplacer
 */
void minHeapify(binary_heap_t * heap, int val);

/**
 * @brief Construit un tas binaire minimum a partir d'un tas binaire quelconque
 * 
 * @param heap Tas binaire quelconque
 */
void buildMinHeap(binary_heap_t * heap);

/**
 * @brief Tri par tas du tableau
 * 
 * @param heap Le tas binaire à trier
 */
void heapSort(binary_heap_t* heap);

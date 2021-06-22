#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include "partition.h"
#include "compoConnexes2.h"

/**
 * @brief Creer les differentes chaines de caracteres utiles pour dessiner le graphe
 * 
 * @param name Nom general des fichiers
 * @param dir Chemin du dossier ou stcoker les fichiers
 * @param dotpath Chemin du fichier .dot 
 * @param pngPath Chemin du fichier png
 * @param command Commande pour transformer le .dot en png
 */
void createStrings(char * name, char * dir, char * dotPath, char * pngPath, char * command);

/**
 * @brief Creer le fichier .dot et le fichier png pour la partition en parametres
 * 
 * @param partition La partition a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawPartitionGraph(partition_t partition, int n, char * name);

/**
 * @brief Creer le fichier .dot et le fichier png pour la matrice d'adjacence en parametres
 * 
 * @param matrix La matrice d'adjacence a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawAdjencyMatrixGraph(int * matrix, int n, char * name);

/**
 * @brief Creer le fichier .dot et le fichier png pour representer un rgaphe sous forme de couples d'aretes + nombre d'aretes
 * 
 * @param graph Le graphe à représenter (sous forme de couples d'aretes + nombre d'aretes)
 */
void drawCouplesGraph(couples_graphe_t sourceGraph, char* name);
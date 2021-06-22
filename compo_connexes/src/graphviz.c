#include "graphviz.h"

/**
 * @brief Creer les differentes chaines de caracteres utiles pour dessiner le graphe
 * 
 * @param name Nom general des fichiers
 * @param dir Chemin du dossier ou stcoker les fichiers
 * @param dotpath Chemin du fichier .dot 
 * @param pngPath Chemin du fichier png
 * @param command Commande pour transformer le .dot en png
 */
void createStrings(char * name, char * dir, char * dotPath, char * pngPath, char * command)
{
    // Chemin du fichier .dot
    strcpy(dotPath, dir);
    strcat(dotPath, name);
    strcat(dotPath, ".dot");
    // Chemin du fichier png
    strcpy(pngPath, dir);
    strcat(pngPath, name);
    strcat(pngPath, ".png");
    // Commande pour le fichier png
    strcpy(command, "dot -Tpng ");
    strcat(command, dotPath);
    strcat(command, " -o ");
    strcat(command, pngPath);
}

/**
 * @brief Libere les choses propres a graphviz
 * 
 * @param graph_context 
 * @param graph 
 */
void freeAll(GVC_t * graph_context, Agraph_t * graph)
{
    //  Libération mémoire du contexte du graphe
    gvFreeLayout(graph_context, graph);
    //  Libération mémoire du graphe
    agclose(graph);
}

/**
 * @brief Genere le fichier .dot du graphe
 * 
 * @param graph_context 
 * @param graph 
 * @param fic 
 */
void generateGraphviz(GVC_t * graph_context, Agraph_t * graph, FILE * fic)
{
    //agwrite(graph, stdout);                      //  Ecriture sur la sortie standard en dot sans formatage
    gvLayout(graph_context, graph, "dot");         //  Permet de dessiner le graphe "correctement"
    gvRender(graph_context, graph, "dot", fic);    //  Génération du fichier .dot
}

/**
 * @brief 
 * 
 * @param command Commande système pour generer une image à partir du fichier .dot
 */
void generatePng(char * command)
{
    int sys;

    sys = system(command);
    if (sys != 0)
    {
        fprintf(stderr, "Impossible de lancer la commande : %s\n", command);
    }
}

/**
 * @brief Creer le fichier .dot et le fichier png pour la partition en parametres
 * 
 * @param partition La partition a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawPartitionGraph(partition_t partition, int n, char * name)
{
    Agraph_t    * graph;
    FILE        * fic;
    GVC_t       * graph_context;
    int           i = 0,
                  j = 0;
    char          indexClasse[3],
                  indexElement[3],
                  dotPath[50],
                  pngPath[50],
                  command[100],
                * dir = "../graphviz/";
    classe_t    * classes;
    element_t   * elements = NULL;

    createStrings(name, dir, dotPath, pngPath, command);

    fic = fopen(dotPath, "w");
    if(fic)
    {
        graph_context = gvContext();
        if (graph_context)
        {
            graph = agopen(name, Agdirected, 0);

            classes = lister_partition(partition, n);

            // Dessine les noeuds
            while(i < n && classes[i] != -1)
            {
                sprintf(indexClasse, "%d", classes[i]);
                agnode(graph, indexClasse, 1);
                i++;
            }

            //Dessine les arretes
            i = 0;
            while(i < n && classes[i] != -1)
            {
                elements = lister_classe(partition, classes[i], n);
                sprintf(indexClasse, "%d", classes[i]);
                while(j < n && elements[j] != -1)
                {
                    sprintf(indexElement, "%d", elements[j]);
                    agedge(graph, agnode(graph, indexElement, 1), agnode(graph, indexClasse, 1), NULL, 1);
                    j++;
                }
                i++;
                j=0;
            }

            generateGraphviz(graph_context, graph, fic);
            generatePng(command);

            free(classes);
            if(elements != NULL) {
                free(elements);
            }
            freeAll(graph_context, graph);
            fclose(fic);
        }
        else
        {
            fprintf(stderr, "Impossible de créer le contexte de graphe...\n");
        }
    }
	else
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier...\n");
    }
}

/**
 * @brief Creer le fichier .dot et le fichier png pour la matrice d'adjacence en parametres
 * 
 * @param matrix La matrice d'adjacence a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawAdjencyMatrixGraph(int * matrix, int n, char * name)
{
    Agraph_t    * graph;
    FILE        * fic;
    GVC_t       * graph_context;
    int           i = 0,
                  j = 0;
    char          nodeName[11],
                  nodeName2[11],
                  dotPath[50],
                  pngPath[50],
                  command[100],
                * dir = "../graphviz/";

    createStrings(name, dir, dotPath, pngPath, command);

    fic = fopen(dotPath, "w");
    if(fic)
    {
        graph_context = gvContext();
        if (graph_context)
        {
            graph = agopen(name, Agundirected, 0);

            // Dessine les noeuds
            for(i = 0; i < n; i++)
            {
                sprintf(nodeName, "%d", i);
                agnode(graph, nodeName, 1);
            }

            // Dessine les arretes
            for(i = 0; i < n; i++)
            {
                for(j = i; j < n; j++)
                {
                    sprintf(nodeName, "%d", i);
                    if(matrix[i*n + j] == 1)
                    {
                        sprintf(nodeName2, "%d", j);
                        agedge(graph, agnode(graph, nodeName, 1), agnode(graph, nodeName2, 1), NULL, 1);
                    }
                }
            }

            generateGraphviz(graph_context, graph, fic);
            generatePng(command);

            freeAll(graph_context, graph);
            fclose(fic);
        }
        else
        {
            fprintf(stderr, "Impossible de créer le contexte de graphe...\n");
        }
    }
	else
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier...\n");
    }
}

void drawCouplesGraph(couples_graphe_t sourceGraph, char* name) {
    Agraph_t    * graphe;
    FILE        * fic;
    GVC_t       * graph_context;
    int           i = 0,
                  sys;
    char          nodeName[11],
                  nodeName2[11],
                  dotPath[50],
                  pngPath[50],
                  command[100],
                * dir = "../graphviz/";
    
    createStrings(name, dir, dotPath, pngPath, command);

    fic = fopen(dotPath, "w");
    if(fic)
    {
        graph_context = gvContext();
        if (graph_context)
        {
            graphe = agopen(name, Agundirected, 0);

            // Dessine les noeuds
            for(i = 0; i < sourceGraph.nbNoeuds; i++)
            {
                sprintf(nodeName, "%d", i);
                agnode(graphe, nodeName, 1);
            }

            // Dessine les arretes
            for (i = 0; i < sourceGraph.nbAretes; i++)
            {
                sprintf(nodeName, "%d", sourceGraph.aretes[i].noeudDeb);
                sprintf(nodeName2, "%d", sourceGraph.aretes[i].noeudFin);
                agedge(graphe, agnode(graphe, nodeName, 1), agnode(graphe, nodeName2, 1), NULL, 1);
            }

            generateGraphviz(graph_context, graphe, fic);
            generatePng(command);

            freeAll(graph_context, graphe);
            fclose(fic);
        }
        else
        {
            fprintf(stderr, "Impossible de créer le contexte de graphe...");
        }
    }
	else
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier...\n");
    }
}
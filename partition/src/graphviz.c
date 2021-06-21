#include "graphviz.h"

void drawPartitionGraph(partition_t partition, int n, char * name)
{
    Agraph_t    * graphe;
    Agnode_t    * noeuds;
    Agedge_t    * arretes;
    FILE        * fic;
    GVC_t       * graph_context;
    int           i,
                  sys;
    char          nom[2],
                  dotPath[50],
                  pngPath[50],
                  command[100],
                * dir = "../graphviz/";

    strcpy(dotPath, dir);
    strcat(dotPath, name);
    strcat(dotPath, ".dot");
    strcpy(pngPath, dir);
    strcat(pngPath, name);
    strcat(pngPath, ".png");

    fic = fopen(dotPath, "w");
    if(fic)
    {
        graph_context = gvContext();
        if (graph_context)
        {
            graphe = agopen(name, Agdirected, 0);

            // Dessine les noeuds
            for(i = 0; i<n; i++)
            {
                sprintf(nom, "%d", partition.foret[i]);
                noeuds = agnode(graphe, nom, 1);
            }

            //Dessine les arretes
            /*for(i = 0; i<n; i++)
            {
                arretes = agedge(graphe, noeuds[i], noeuds[recuperer_classe(partition, partition.foret[i])], NULL, 1);
            }*/

            //  Ecriture sur la sortie standard en dot sans formatage
            //agwrite(graphe, stdout);

            //  Permet de dessiner le graphe "correctement"
            gvLayout(graph_context, graphe, "dot");

            //  Génération du fichier .dot
            gvRender(graph_context, graphe, "dot", fic);

            //  Commande système pour généer une image à partir du fichier .dot
            strcpy(command, "dot -Tpng ");
            strcat(command, dotPath);
            strcat(command, " -o ");
            strcat(command, pngPath);
            sys = system(command);
            if (sys != 0)
            {
                fprintf(stderr, "Impossible de lancer la commande : %s", command);
            }

            //  Libération mémoire du contexte du graphe
            gvFreeLayout(graph_context, graphe);

            //  Libération mémoire du graphe
            agclose(graphe);

            //  Fermeture du fichier
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

void partitionSimple()
{
	partition_t   test;
    int           n;

    n = 10;
    test = creer(n);

    //afficherForet(test);

    fusion(test, test.foret[1], test.foret[4]);
    //afficherForet(test);
    fusion(test, test.foret[9], test.foret[3]);
    //afficherForet(test);

    drawPartitionGraph(test, n, "partitionSimple");
    
    detruirePartition(&test);
}

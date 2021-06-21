#include "graphviz.h"

void partitionSimple()
{
    partition_t   test;
    Agraph_t    * graphe;
    Agnode_t   ** noeuds;
    FILE        * fic;
    GVC_t       * graph_context;
    int           i,
                  sys;
    char          nom[2];
    int 	  n = 11;

    noeuds = malloc(sizeof(Agnode_t *) * n);
    if(noeuds == NULL) {
	fputs("erreur allocation de memoire pour les neouds\n", stderr);
        return;
    }
    fic = fopen("partitionSimple.dot", "w");
    if(fic)
    {
        test = creer(n);
        graph_context = gvContext();
        if (graph_context)
        {
            graphe = agopen("PartitionSimple", Agdirected, 0);
            for(i = 0; i<n; i++)
            {
                sprintf(nom, "%d", test.foret[i]);
                noeuds[i] = agnode(graphe, nom, 1);
            }

            //  Ecriture sur la sortie standard en dot sans formatage
            agwrite(graphe, stdout);

            //  Permet de dessiner le graphe "correctement"
            gvLayout(graph_context, graphe, "dot");

            //  Génération du fichier .dot
            gvRender(graph_context, graphe, "dot", fic);

            //  Commande système pour généer une image à partir du fichier .dot
            sys = system("dot -Tpng partitionSimple.dot -o partitionSimple.png");
            if (sys != 0)
            {
                fprintf(stderr, "Impossible de lancer la commande : dot -Tpng partitionSimple.dot -o partitionSimple.png");
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
        fprintf(stderr, "Impossible d'ouvrir le fichier...");
    }
}

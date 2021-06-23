#include "dijkstra.h"

bool dijkstra(graphe_t graphe, int source, int cible, int *chemin, int n) {
	binary_heap_t tas;
	bool found = false;
	int *prec, cour;

	tas.array = malloc(sizeof(int) * n);
	if(tas.array == NULL) {
		fputs("erreur malloc dijkstra\n", stderr);
		return false;
	}
	tas.length = n;
	heapSize = n;
	for(i = 0; i < n; ++i) {
		tas.array[i] = INT_MAX;
	}
	tas.array[source] = 0;
	while(found == false) {
        	cour = min();
		if(cour != cible) {
			for() {//for each neighbor v of u
				alt = dist[u] + length(u, v)
				if(alt < dist[v]) {
					dist[v] = alt;
					prev[v] = u;
			                if(trouve[node] == false) {
						Q.decrease_priority(v, alt)
					}
					else {
						add;
					}
				}
			}
		}
		else {
			found == true;
			//nettoyer
		}
	}
	return dist, prev;
}

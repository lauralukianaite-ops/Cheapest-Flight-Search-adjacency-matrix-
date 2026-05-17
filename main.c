#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(){
    Graph graph;
    init_graph(&graph);

    int vilnius = get_city_index(&graph,"Vilnius");
    int ryga = get_city_index(&graph,"Ryga");
    int talinas = get_city_index(&graph,"Talinas");

    int vilnius2 = get_city_index(&graph,"Vilnius");

    add_flight(&graph, "Vilnius", "Ryga", 50);
    add_flight(&graph, "Ryga", "Talinas", 100);
    add_flight(&graph, "Vilnius", "Talinas", 250);

    printf("Vilnius -> Ryga kaina: %d EUR (turi buti 50)\n", graph.adj_matrix[vilnius][ryga]);
    printf("Ryga -> Londonas kaina: %d EUR (turi buti 100)\n", graph.adj_matrix[ryga][talinas]);
    printf("Vilnius -> Londonas kaina: %d EUR (turi buti 250)\n", graph.adj_matrix[vilnius][talinas]);
    printf("Londonas -> Vilnius kaina: %d (turi buti %d, nes skrydzio atgal nera)\n", 
           graph.adj_matrix[talinas][vilnius], NO_FLIGHT);

    printf("\nIs viso unikaliu miestu grafe: %d\n", graph.city_count);
    

    return 0;
}
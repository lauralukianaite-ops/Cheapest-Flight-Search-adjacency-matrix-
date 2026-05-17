#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(){
    Graph graph;
    init_graph(&graph);

    add_flight(&graph, "Vilnius", "Ryga", 50);
    add_flight(&graph, "Ryga", "Londonas", 100);
    add_flight(&graph, "Vilnius", "Londonas", 250); 
    add_flight(&graph, "Vilnius", "Kopenhaga", 70);
    add_flight(&graph, "Kopenhaga", "Londonas", 60); 
    add_flight(&graph, "Tokijas", "Pekinas", 180);

    find_cheapest_route(&graph, "Vilnius", "Londonas");
    find_cheapest_route(&graph, "Vilnius", "Tokijas");

    return 0;
}
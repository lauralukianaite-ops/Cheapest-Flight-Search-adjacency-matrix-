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

    printf("Vilniaus indx: %d\n", vilnius);
    printf("Rygos indx: %d\n", ryga);
    printf("Talino indx: %d\n", talinas);
    printf("Vilniaus indx: %d\n", vilnius2);

    printf("\nIs viso unikaliu miestu grafe: %d\n", graph.city_count);
    

    return 0;
}
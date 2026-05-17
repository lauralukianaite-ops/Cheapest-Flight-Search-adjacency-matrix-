#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void init_graph(Graph *g){
    g->city_count = 0;

    for(int i=0; i<MAX_CITIES; i++){
        for(int j=0; j<MAX_CITIES; j++){
            if(i==j){
                g->adj_matrix[i][j] = 0;
            } else {
                g->adj_matrix[i][j] = NO_FLIGHT;
            }
        }
    }
}

int get_city_index(Graph *g, char *name){

    //rastas jau zinomas miestas
    for(int i=0; i<g->city_count; i++){
        if(strcmp(g->cities[i].name, name) == 0){
            return i;
        }
    }

    //tokio miesto dar nebuvo
    if(g->city_count >=MAX_CITIES){
        printf("Klaida! Viršytas maksimalus miestų skaičius!");
        exit(1);
    }

    strcpy(g->cities[g->city_count].name, name);
    g->city_count++;

    return g->city_count -1;
}
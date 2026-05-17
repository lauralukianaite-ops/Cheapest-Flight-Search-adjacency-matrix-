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

void add_flight(Graph *g, char *from, char *to, int price){
    int from_idx = get_city_index(g, from);
    int to_idx = get_city_index(g, to);

    g->adj_matrix[from_idx][to_idx] = price;
}

void find_cheapest_route(Graph *g, char *start_city, char *end_city){

    //randami miestų indeksai
    int start_idx = -1, end_idx = -1;
    for(int i=0; i<g->city_count; i++){
        if (strcmp(g->cities[i].name, start_city) == 0) start_idx = i;
        if (strcmp(g->cities[i].name, end_city) == 0) end_idx = i;
    }

    if (start_idx == -1 || end_idx == -1) {
        printf("Klaida: Pradinis arba galinis miestas nerastas skrydziu sarase!\n");
        return;
    }

    int dist[MAX_CITIES][MAX_CITIES];
    int next_node[MAX_CITIES][MAX_CITIES];

    for(int i=0; i<g->city_count; i++){
        for(int j=0; j<g->city_count; j++){
            dist[i][j] = g->adj_matrix[i][j];
            if(g->adj_matrix[i][j] != NO_FLIGHT && i != j){
                next_node[i][j] = j;
            } else {
                next_node[i][j] = -1;
            }
        }
    }

    //Floido-Varšalo algoritmas
    for(int k=0; k<g->city_count; k++){
        for(int i=0; i<g->city_count; i++){
            for(int j=0; j<g->city_count; j++){
                if(dist[i][k] != NO_FLIGHT && dist[k][j] != NO_FLIGHT && dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_node[i][j] = next_node[i][k];
                }
            }
        }
    }

    if (dist[start_idx][end_idx] == NO_FLIGHT) {
        printf("Marsrutas iš %s į %s NEEGZISTUOJA.\n", start_city, end_city);
    } else {
        printf("Pigiausio skrydžio kaina iš %s į %s: %d EUR\n", start_city, end_city, dist[start_idx][end_idx]);
        
        printf("Maršrutas: %s", start_city);
        int curr = start_idx;
        while (curr != end_idx) {
            curr = next_node[curr][end_idx];
            printf(" -> %s", g->cities[curr].name);
        }
        printf("\n");
    }

}
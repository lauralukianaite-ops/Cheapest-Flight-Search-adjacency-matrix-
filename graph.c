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

    if (g->adj_matrix[from_idx][to_idx] == NO_FLIGHT || price < g->adj_matrix[from_idx][to_idx]) {
        g->adj_matrix[from_idx][to_idx] = price;
    }
}

FlightResult find_cheapest_route(Graph *g, int start_idx, int end_idx){
    FlightResult res = {0};

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

    //Floyd-Warshall algoritmas
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
        res.found = 0;
        return res;
    }

    res.found = 1;
    res.total_cost = dist[start_idx][end_idx];

    int curr = start_idx;
    res.path[res.path_len++] = curr;
    while (curr != end_idx) {
        curr = next_node[curr][end_idx];
        res.path[res.path_len++] = curr;
    }

    return res;
}
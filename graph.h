#ifndef GRAFAS_H
#define GRAFAS_H

#define MAX_CITIES 100
#define MAX_NAME_LEN 50
#define NO_FLIGHT -1

typedef struct {
    char name[MAX_NAME_LEN];
} City;

typedef struct {
    City cities[MAX_CITIES];
    int city_count;
    int adj_matrix[MAX_CITIES][MAX_CITIES];
} Graph;

void init_graph(Graph *g);
int get_city_index(Graph *g, char *name);

#endif
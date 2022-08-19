#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "stack.h"
#include "maths.h"
#include <math.h>
#define x_max 80
#define y_max 25

typedef struct Graph {
    char **matrix;
} Graph;

void init_graph(Graph *graph);
void clear_memory(Graph *graph);
void update_graph(Graph *graph, char *input);
void draw(Graph *graph);

int main() {
    Graph *graph = malloc(sizeof(Graph));
    init_graph(graph);
    char str[1024];
    fgets(str, 1024, stdin);
    char *parsed = parser(str);
    update_graph(graph, parsed);
    draw(graph);
    clear_memory(graph);
    free(parsed);
}

void init_graph(Graph *graph) {
    graph->matrix = malloc(y_max * sizeof(char*));
    for (int i = 0; i < y_max; i++) {
        graph->matrix[i] = malloc(x_max * sizeof(char));
    }
    for (int i = 0; i < y_max; i++) {
        for (int j = 0; j < x_max; j++) {
            graph->matrix[i][j] = '.';
        }
    }
}
void clear_memory(Graph *graph) {
    for (int i = 0; i < y_max; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

void update_graph(Graph *graph, char *input) {
    int count = 0;
    for (double i = 0; i <= 4.0 * M_PI; i += (4.0 * M_PI) / 80.0) {
        double point = calculate(input, i);
        int temp = round(point * 12);
        if (temp <= 12 && temp >= -12) {
            graph->matrix[12 + temp][count] = '*';
        }
        count++;
    }
}

void draw(Graph *graph) {
    for (int i = 0; i < y_max; i++) {
        for (int j = 0; j < x_max; j++) {
            printf("%c", graph->matrix[i][j]);
        }
        if (i != y_max - 1)
            printf("\n");
    }
}

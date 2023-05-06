#include <stdio.h>
#include <stdlib.h>

#define INF 999

struct Edge {
    int source, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
}

struct Subset {
    int parent;
    int rank;
};

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    }
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compare(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*) a;
    struct Edge* b1 = (struct Edge*) b;
    return a1->weight > b1->weight;
}

void Kruskals(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);
    struct Subset* subsets = (struct Subset*) malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];
        int x = find(subsets, next_edge.source);
        int y = find(subsets, next_edge.dest);
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    printf("Minimum Spanning Tree:\n");
    int minCost = 0;
    for (i = 0; i < e; ++i) {
        printf("(%d, %d) -> %d\n", result[i].source, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }
    printf("Minimum Cost: %d", minCost);
}

int main() {
    int V, E, source, dest, weight;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    struct Graph* graph = createGraph(V, E);
    for (int i = 0; i < E; ++i) {
        printf("Enter source, destination, and weight of edge %d: ", i + 1);
        scanf("%d %d %d", &source, &dest, &weight);
        graph->edge[i].source = source;
        graph->edge[i].dest = dest;
        graph->edge[i].weight = weight;
    }

    // Print adjacency matrix
int adjMatrix[V][V];

for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
        if (i == j) {
            adjMatrix[i][j] = 0;
        } else {
            adjMatrix[i][j] = INF;
        }
    }
}
for (int i = 0; i < E; ++i) {
    int source = graph->edge[i].source;
    int dest = graph->edge[i].dest;
    int weight = graph->edge[i].weight;
    adjMatrix[source][dest] = weight;
    adjMatrix[dest][source] = weight; // assuming undirected graph
}
printf("Adjacency matrix:\n");
for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
        if (adjMatrix[i][j] == INF) {
            printf("999 ");
        } else {
            printf("%d   ", adjMatrix[i][j]);
        }
    }
    printf("\n");
}

    Kruskals(graph);
    return 0;
}

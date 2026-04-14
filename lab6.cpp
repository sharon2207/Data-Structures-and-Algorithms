#include <stdio.h>
#include <stdlib.h>

#define INF 9999

// --------- Structure for Kruskal ---------
typedef struct {
    int u, v, w;
} Edge;

int parent[50];

// Find parent for union find
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Union of sets
void unionSet(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

// --------- PRIM’S ALGORITHM ---------
void prim(int graph[50][50], int n) {
    int selected[50] = {0};
    int no_edge = 0;
    selected[0] = 1;

    printf("\n--- PRIM'S MST (Hospital Department Connections) ---\n");

    while (no_edge < n - 1) {
        int min = INF;
        int x = 0, y = 0;

        for (int i = 0; i < n; i++) {
            if (selected[i]) {
                for (int j = 0; j < n; j++) {
                    if (!selected[j] && graph[i][j] != 0 && graph[i][j] < min) {
                        min = graph[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        printf("Connect Dept %d -> Dept %d (Cost = %d)\n", x, y, graph[x][y]);
        selected[y] = 1;
        no_edge++;
    }
}

// --------- KRUSKAL’S ALGORITHM ---------
void kruskal(int graph[50][50], int n) {
    Edge edges[200];  
    int edgeCount = 0;

    // Convert adjacency matrix to edge list
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != 0 && graph[i][j] != INF) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].w = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges by weight
    for (int i = 0; i < edgeCount; i++) {
        for (int j = i + 1; j < edgeCount; j++) {
            if (edges[i].w > edges[j].w) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    printf("\n--- KRUSKAL'S MST (Hospital Department Connections) ---\n");

    int count = 0, i = 0;
    while (count < n - 1 && i < edgeCount) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            printf("Connect Dept %d -> Dept %d (Cost = %d)\n", u, v, w);
            unionSet(u, v);
            count++;
        }
        i++;
    }
}

// --------- MAIN PROGRAM ---------
int main() {
    int n;
    int graph[50][50];

    printf("Enter number of hospital departments: ");
    scanf("%d", &n);

    printf("\nEnter the cost matrix (Use 0 for no connection):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = INF;
        }
    }

    prim(graph, n);
    kruskal(graph, n);

    return 0;
}


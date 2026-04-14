#include <stdio.h>
#include <stdlib.h>

#define INF 99999

// ---------- Function to Print Distance Matrix ----------
void printMatrix(int V, int dist[50][50]) {
    printf("\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// ---------- Print Path ----------
void printPath(int parent[50][50], int src, int dest) {
    if (src == dest) {
        printf("%d", src);
        return;
    }
    if (parent[src][dest] == -1) {
        printf("No Path");
        return;
    }

    printPath(parent, src, parent[src][dest]);
    printf(" -> %d", dest);
}

int main() {

    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    if (V <= 0 || V > 50) {
        printf("Invalid vertex count! (1–50 allowed)\n");
        return 0;
    }

    int dist[50][50];
    int parent[50][50];

    // Initialize matrices
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                dist[i][j] = 0;
                parent[i][j] = -1;
            } else {
                dist[i][j] = INF;
                parent[i][j] = -1;
            }
        }
    }

    printf("Enter number of edges: ");
    scanf("%d", &E);

    if (E < 0) {
        printf("Invalid number of edges!\n");
        return 0;
    }

    int directed;
    printf("Is the graph directed? (1 = Yes, 0 = No): ");
    scanf("%d", &directed);

    printf("\nEnter edges in format: src dest cost\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        if (u < 0 || u >= V || v < 0 || v >= V) {
            printf("Invalid edge (%d, %d)! Skipping...\n", u, v);
            continue;
        }

        dist[u][v] = w;
        parent[u][v] = u;

        if (!directed) {
            dist[v][u] = w;
            parent[v][u] = v;
        }
    }

    printf("\nInitial Distance Matrix:\n");
    printMatrix(V, dist);

    // ------------- FLOYD–WARSHALL -----------------
    for (int k = 0; k < V; k++) {
        printf("\nConsidering intermediate vertex: %d\n", k);

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                if (dist[i][k] == INF || dist[k][j] == INF)
                    continue;

                int newDist = dist[i][k] + dist[k][j];

                if (newDist < dist[i][j]) {
                    dist[i][j] = newDist;
                    parent[i][j] = parent[k][j];
                }
            }
        }

        printMatrix(V, dist);
    }

    // -------- Negative Cycle Detection --------
    int hasNegativeCycle = 0;
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0)
            hasNegativeCycle = 1;
    }

    if (hasNegativeCycle)
        printf("\n*** WARNING: Graph contains a NEGATIVE CYCLE! ***\n");
    else
        printf("\nNo negative cycles detected.\n");

    // -------- Final Matrix --------
    printf("\nFinal All-Pairs Shortest Path Matrix:\n");
    printMatrix(V, dist);

    // -------- Path Printing --------
    printf("\nDo you want to print path between two vertices? (1/0): ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        int s, d;
        printf("Enter source and destination: ");
        scanf("%d %d", &s, &d);

        if (s < 0 || s >= V || d < 0 || d >= V)
            printf("Invalid vertices!\n");
        else if (dist[s][d] == INF)
            printf("No path exists.\n");
        else {
            printf("\nShortest Distance = %d\n", dist[s][d]);
            printf("Path: ");
            printPath(parent, s, d);
            printf("\n");
        }
    }

    return 0;
}


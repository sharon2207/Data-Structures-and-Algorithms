#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF 9999

int minDistance(int dist[], int visited[], int n) {
    int min = INF, min_index = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX][MAX], int n, int src, char dept[][50]) {
    int dist[MAX], visited[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    printf("\n--- Intermediate Trace (Relaxations) ---\n");

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        visited[u] = 1;

        printf("\nSelected Department: %s (Distance = %d)\n", dept[u], dist[u]);

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0 && 
                dist[u] + graph[u][v] < dist[v]) {

                printf("Updating Distance of %s from %d to %d\n",
                       dept[v], dist[v], dist[u] + graph[u][v]);

                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\n--- Final Shortest Distances from Source (%s) ---\n", dept[src]);
    for (int i = 0; i < n; i++) {
        printf("%s -> %s : %d minutes\n", dept[src], dept[i], dist[i]);
    }
}

int main() {
    int n;
    char dept[MAX][50];
    int graph[MAX][MAX];
    
    printf("Enter number of hospital departments: ");
    scanf("%d", &n);

    printf("\nEnter department names:\n");
    for (int i = 0; i < n; i++) {
        printf("Dept %d: ", i);
        scanf("%s", dept[i]);
    }

    printf("\nEnter time (in minutes) to transfer between departments.\n");
    printf("Enter 0 if no direct connection.\n");

    for (int i = 0; i < n; i++) {
        printf("\n--- Enter times FROM %s ---\n", dept[i]);
        for (int j = 0; j < n; j++) {
            printf("Time from %s -> %s: ", dept[i], dept[j]);
            scanf("%d", &graph[i][j]);
        }
    }

    int src;
    printf("\nEnter Source Department Index (0 to %d): ", n - 1);
    scanf("%d", &src);

    dijkstra(graph, n, src, dept);

    return 0;
}


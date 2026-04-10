#include <stdio.h>
#include <stdlib.h>

#define MAX 20

// Structure for adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Structure for graph
struct Graph {
    int numVertices;
    struct Node* adjList[MAX];
};

// Queue for BFS
int queue[MAX], front = -1, rear = -1;

// Function prototypes
void createGraph(struct Graph* graph);
void addEdge(struct Graph* graph, int src, int dest);
void BFS(struct Graph* graph, int start);
void DFS(struct Graph* graph, int start, int visited[]);
void traversalMenu(struct Graph* graph);
void topologicalSort(struct Graph* graph);
void topologicalSortUtil(struct Graph* graph, int v, int visited[], int stack[], int* top);
int isCyclic(struct Graph* graph);
int isCyclicUtil(struct Graph* graph, int v, int visited[], int recStack[]);
void enqueue(int val);
int dequeue();
int isEmpty();

// ============================ MAIN FUNCTION ============================
int main() {
    struct Graph graph;
    graph.numVertices = 0;
    for (int i = 0; i < MAX; i++)
        graph.adjList[i] = NULL;

    int choice;
    while (1) {
        printf("\n===== DIRECTED GRAPH MENU =====");
        printf("\n1. Create Graph");
        printf("\n2. Check DAG (Acyclic or Not)");
        printf("\n3. Traversal (BFT & DFT)");
        printf("\n4. Topological Sort");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createGraph(&graph);
                break;
            case 2:
                if (graph.numVertices == 0) {
                    printf("Graph not created yet!\n");
                    break;
                }
                if (isCyclic(&graph))
                    printf("? The graph contains a cycle (Not a DAG).\n");
                else
                    printf("? The graph is Acyclic (DAG).\n");
                break;
            case 3:
                if (graph.numVertices == 0) {
                    printf("Graph not created yet!\n");
                    break;
                }
                traversalMenu(&graph);
                break;
            case 4:
                if (graph.numVertices == 0) {
                    printf("Graph not created yet!\n");
                    break;
                }
                topologicalSort(&graph);
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

// ============================ GRAPH CREATION ============================
void createGraph(struct Graph* graph) {
    printf("Enter number of vertices: ");
    scanf("%d", &graph->numVertices);

    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < graph->numVertices; i++)
        graph->adjList[i] = NULL;

    printf("Enter edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Graph created successfully.\n");
}

// Add directed edge
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// ============================ BFS TRAVERSAL ============================
void BFS(struct Graph* graph, int start) {
    int visited[MAX] = {0};
    enqueue(start);
    visited[start] = 1;

    printf("BFS starting from vertex %d: ", start);
    while (!isEmpty()) {
        int v = dequeue();
        printf("%d ", v);
        struct Node* temp = graph->adjList[v];
        while (temp) {
            int adj = temp->vertex;
            if (!visited[adj]) {
                visited[adj] = 1;
                enqueue(adj);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// ============================ DFS TRAVERSAL ============================
void DFS(struct Graph* graph, int start, int visited[]) {
    visited[start] = 1;
    printf("%d ", start);

    struct Node* temp = graph->adjList[start];
    while (temp) {
        int adj = temp->vertex;
        if (!visited[adj])
            DFS(graph, adj, visited);
        temp = temp->next;
    }
}

// ============================ TRAVERSAL MENU ============================
void traversalMenu(struct Graph* graph) {
    int start;
    printf("Enter starting vertex: ");
    scanf("%d", &start);

    printf("\n--- Breadth First Traversal ---\n");
    BFS(graph, start);

    printf("\n--- Depth First Traversal ---\n");
    int visited[MAX] = {0};
    DFS(graph, start, visited);
    printf("\n");
}

// ============================ TOPOLOGICAL SORT ============================
void topologicalSort(struct Graph* graph) {
    int visited[MAX] = {0};
    int stack[MAX], top = -1;

    for (int i = 0; i < graph->numVertices; i++)
        if (!visited[i])
            topologicalSortUtil(graph, i, visited, stack, &top);

    printf("Topological Order: ");
    while (top >= 0)
        printf("%d ", stack[top--]);
    printf("\n");
}

void topologicalSortUtil(struct Graph* graph, int v, int visited[], int stack[], int* top) {
    visited[v] = 1;
    struct Node* temp = graph->adjList[v];
    while (temp) {
        if (!visited[temp->vertex])
            topologicalSortUtil(graph, temp->vertex, visited, stack, top);
        temp = temp->next;
    }
    stack[++(*top)] = v;
}

// ============================ CYCLE DETECTION ============================
int isCyclic(struct Graph* graph) {
    int visited[MAX] = {0};
    int recStack[MAX] = {0};

    for (int i = 0; i < graph->numVertices; i++)
        if (isCyclicUtil(graph, i, visited, recStack))
            return 1;
    return 0;
}

int isCyclicUtil(struct Graph* graph, int v, int visited[], int recStack[]) {
    if (!visited[v]) {
        visited[v] = 1;
        recStack[v] = 1;

        struct Node* temp = graph->adjList[v];
        while (temp) {
            int adj = temp->vertex;
            if (!visited[adj] && isCyclicUtil(graph, adj, visited, recStack))
                return 1;
            else if (recStack[adj])
                return 1;
            temp = temp->next;
        }
    }
    recStack[v] = 0;
    return 0;
}

// ============================ QUEUE FUNCTIONS ============================
void enqueue(int val) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = val;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

int isEmpty() {
    return (front == -1 || front > rear);
}


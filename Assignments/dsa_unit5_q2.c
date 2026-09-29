#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 50
#define INF INT_MAX

// Function to find the vertex with minimum distance value from the set of unvisited vertices
int getMinDistanceVertex(int dist[], bool visited[], int n) {
    int min = INF;
    int minIndex = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function implementing Dijkstra's algorithm
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int n, int src) {
    int dist[MAX_VERTICES];      // dist[i] holds shortest distance from src to i
    bool visited[MAX_VERTICES];  // visited[i] is true if vertex i is finalized

    // Initialize all distances to infinity and visited array to false
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        int u = getMinDistanceVertex(dist, visited, n);

        // If remaining vertices are unreachable, break early
        if (u == -1 || dist[u] == INF) {
            break;
        }

        visited[u] = true;

        // Update dist[v] for adjacent vertices of u
        for (int v = 0; v < n; v++) {
            // Update dist[v] only if:
            // 1. It is not finalized (not visited)
            // 2. There is an edge from u to v (graph[u][v] != 0)
            // 3. Total weight of path from src to v through u is less than current dist[v]
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INF 
                && (dist[u] + graph[u][v] < dist[v])) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Display shortest path results
    printf("\n============================================\n");
    printf(" Shortest Distances from Source City (Vertex %d)\n", src);
    printf("============================================\n");
    printf("%-15s %-20s\n", "Destination", "Minimum Cost / Distance");
    printf("--------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("City %-10d %-20s\n", i, "Unreachable");
        } else {
            printf("City %-10d %-20d\n", i, dist[i]);
        }
    }
    printf("============================================\n");
}

int main() {
    int n, src;
    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the number of cities/vertices (minimum 5): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("\nEnter the cost adjacency matrix (%d x %d):\n", n, n);
    printf("(Enter 0 if there is no direct road between two cities)\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nEnter the source city (0 to %d): ", n - 1);
    if (scanf("%d", &src) != 1 || src < 0 || src >= n) {
        printf("Invalid source city.\n");
        return 1;
    }

    dijkstra(graph, n, src);

    return 0;
}
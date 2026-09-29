#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 50

// Queue implementation for BFS
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }
    int item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

// Breadth-First Search Traversal
void bfsTraversal(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int n, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    Queue q;
    initQueue(&q);

    // Mark start vertex visited and push to queue
    visited[startVertex] = true;
    enqueue(&q, startVertex);

    printf("\nTraversal visit order starting from vertex %d:\n", startVertex);

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("%d ", current);

        // Check all adjacent vertices
        for (int neighbor = 0; neighbor < n; neighbor++) {
            // An edge exists and neighbor hasn't been processed yet
            if (adjMatrix[current][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true; // Mark immediately to prevent duplicate queuing
                enqueue(&q, neighbor);
            }
        }
    }
    printf("\n");

    // Check for unreachable vertices (relevant for disconnected/partially connected graphs)
    bool hasUnvisited = false;
    printf("\nUnvisited / unreachable vertices from vertex %d: ", startVertex);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("%d ", i);
            hasUnvisited = true;
        }
    }
    if (!hasUnvisited) {
        printf("None (Graph is fully reachable/connected from source)");
    }
    printf("\n");
}

int main() {
    int n, startVertex;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];

    printf("Enter number of vertices/locations (n): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the Adjacency Matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
    }

    printf("Enter the starting vertex (0 to %d): ", n - 1);
    if (scanf("%d", &startVertex) != 1 || startVertex < 0 || startVertex >= n) {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    bfsTraversal(adjMatrix, n, startVertex);

    return 0;
}
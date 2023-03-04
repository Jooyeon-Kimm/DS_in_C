#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if(!((p)=malloc(s))){fprintf(stderr,"메모리 부족\n");exit(1);}
#define CALLOC(p,n,s) if(!((p)=calloc(n,s))){fprintf(stderr,"메모리 부족\n");exit(1);}
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10001

typedef int element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(char* message) {
    perror("Error");
    exit(1);
}

void queue_init(QueueType * q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType * q) {
    return (q->front == q->rear);
}

int is_full(QueueType * q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType * q, element item) {
    if (is_full(q))
        error("overflow");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType * q) {
    if (is_empty(q))
        error("underflow");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];

void graph_init(GraphType * g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType * g, int v) {
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "overflow");
        return;
    }
    g->n++;
}

void insert_edge(GraphType * g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "graph index error");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void bfs_mat(GraphType * g, int v) {
    int w;
    QueueType q;

    queue_init(&q);
    visited[v] = TRUE;
    printf("%d ", v);
    enqueue(&q, v);
    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = 0; w < g->n; w++)
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                printf("%d ", w);
                enqueue(&q, w);
            }
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    for (int i = 0; i < 8; i++)
        insert_vertex(g, i);

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);

    insert_edge(g, 1, 0);
    insert_edge(g, 1, 3);
    insert_edge(g, 1, 4);

    insert_edge(g, 2, 0);
    insert_edge(g, 2, 5);
    insert_edge(g, 2, 6);

    insert_edge(g, 3, 1);
    insert_edge(g, 3, 7);

    insert_edge(g, 4, 1);
    insert_edge(g, 4, 7);

    insert_edge(g, 5, 2);
    insert_edge(g, 5, 7);

    insert_edge(g, 6, 2);
    insert_edge(g, 6, 7);

    insert_edge(g, 7, 3);
    insert_edge(g, 7, 4);
    insert_edge(g, 7, 5);
    insert_edge(g, 7, 6);

    printf("Result:\n");

    printf("BFS(7): ");
    bfs_mat(g, 7);


    printf("\n");
    free(g);
    return 0;

}
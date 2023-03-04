#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100 // vertext가 10개이면 입력받는 최대 정수 개수: 9 + 8 + 7 + ... + 3 + 2 + 1 = 45
#define MALLOC(p,s)\
    if (!((p) = malloc(s))) {\
    	fprintf(stderr, "Insufficient memory.");\
        exit(EXIT_FAILURE);\
    }


typedef struct node {
    int vertex;
    struct node* next;
}node;
typedef node* nodePointer;
node* createNode(int);

typedef struct Graph {
    int numVertices;
    nodePointer* adjLists;
}Graph;

// 노드 생성 함수
node* createNode(int v) {
    nodePointer newNode;
    MALLOC(newNode, sizeof(node));

    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 그래프 생성 함수
Graph* createGraph(int vertices) {
    Graph* graph;
    MALLOC(graph, sizeof(graph));
    graph->numVertices = vertices;

    MALLOC(graph->adjLists, sizeof(node*) * vertices);
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// edge 추가 함수
void addEdge(Graph* graph, int s, int d) {
    // edge 추가: 방향 s -> d
    node* newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;

    // edge 추가: 방향 d -> s
    newNode = createNode(s);
    newNode->next = graph->adjLists[d];
    graph->adjLists[d] = newNode;

}

// 그래프 출력 함수
void printGraph(Graph* graph, int v) {
    for (v = 0; v < graph->numVertices; v++) {
        node* temp = graph->adjLists[v];
        printf("\n Vertex %d:\n", v);
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


int main() {
    FILE* fp;
    int read[MAX];
    int idx = 0;
    int i, k, iter = 0; // iteration

    fp = fopen("in1.txt", "rt");

    if (fp == NULL) {
        perror("Error Openeing File!");
        exit(1);
    }
    while (!feof(fp)) {
        fscanf(fp, "%d", &read[idx++]);
    }

    int numOfVertex = read[0]; // vertices
    for (i = 1; i < numOfVertex; i++) {
        iter += i;
    }

    // 01 02 03 04    1-4
    // 12 13 14       5-7
    // 23 24          8-9
    // 34              10

    Graph* graph = createGraph(numOfVertex);
    int z = 1;
    for (i = 0; i < numOfVertex-1; i++) {
        for (k = i + 1; k < numOfVertex; k++) {
            if (read[z++] == 1) {
                addEdge(graph, i, k);
            }
        }
    }
    
    printGraph(graph, numOfVertex);

    return 0;
}
​
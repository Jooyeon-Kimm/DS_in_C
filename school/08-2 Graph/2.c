#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define FALSE 0
#define TRUE 1
short int visited[MAX_VERTICES];

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
    MALLOC(graph, sizeof(*graph));
    graph->numVertices = vertices;

    MALLOC(graph->adjLists, sizeof(node*) * vertices);
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// edge 추가 함수
void addEdge(Graph* graph, int s, int d) {
    nodePointer newNode;

    // edge 추가: 방향 d -> s
    newNode = createNode(s);
    newNode->next = graph->adjLists[d];
    graph->adjLists[d] = newNode;

    // edge 추가: 방향 s -> d
    newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;

}




// 그래프 출력 함수
void printGraph(Graph* graph, int v) {
    for (v = 0; v < graph->numVertices; v++) {
        nodePointer temp = graph->adjLists[v];
        // reverse(temp);
        printf("\n Vertex %d:\n", v);
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


void DFS(Graph* graph, int v) {
    //재귀로 구현, 
    nodePointer temp;
    visited[v] = 1;
    printf("%d ", v);
    for (temp = graph->adjLists[v]; temp; temp = temp->next) {
        if (!visited[temp->vertex]) {
            DFS(graph, temp->vertex);
        }
    }
}


int main() {
    FILE* fp;
    int read[MAX_VERTICES];
    int idx = 0;
    int i, k, iter = 0; // iteration

    fp = fopen("in.txt", "rt");

    if (fp == NULL) {
        perror("Error Openeing File!");
        exit(1);
    }
    while (!feof(fp)) {
        fscanf(fp, "%d", &read[idx++]);
    }

    int numOfVertex = read[0]; // vertices

    Graph* graph = createGraph(numOfVertex);
    int z = 1;
    for (i = 0; i < numOfVertex - 1; i++) {
        for (k = i + 1; k < numOfVertex; k++) {
            if (read[z++] == 1) {
                addEdge(graph, i, k);
            }
        }
    }

    printGraph(graph, numOfVertex);

  
    int cnt = 0;
    for (int i = 0; i < numOfVertex; i++)
    {
        if (!visited[i])
        {
            DFS(graph, i);
            cnt++;
        }
    }
    printf("cnt: %d\n", cnt);


    return 0;
}

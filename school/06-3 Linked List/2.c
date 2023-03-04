#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct node* nodePointer;
typedef struct node {
    nodePointer lLink;
    int data;
    nodePointer rLink;
} Node;

void dInsert(nodePointer node, int data);
void dDelete(nodePointer node, nodePointer deleted);
void printForward(nodePointer head);
void printReverse(nodePointer head);

int main() {
    FILE* file = fopen("in.txt", "r");
    nodePointer head = malloc(sizeof(Node));
    head->lLink = head;
    head->rLink = head;

    while (!feof(file)) {
        int val;
        fscanf(file, "%d", &val);
        dInsert(head, val);
    }

    printForward(head);
    printReverse(head);

    fclose(file);
    return 0;
}

void dInsert(nodePointer node, int data) {
    nodePointer newNode = malloc(sizeof(Node));

    newNode->data = data;
    newNode->lLink = node;
    newNode->rLink = node->rLink;

    node->rLink->lLink = newNode;
    node->rLink = newNode;
}

void dDelete(nodePointer node, nodePointer deleted) {
    if (node == deleted)
        printf("Deletion of head node not permitted\n");
    else {
        deleted->lLink->rLink = deleted->rLink;
        deleted->rLink->lLink = deleted->lLink;
        free(deleted);
    }
}

void printReverse(nodePointer head) {
    nodePointer iterator = head->rLink;
    for (; iterator != head; iterator = iterator->rLink) {
        printf("%5d", iterator->data);
    }
    printf("\n");
}

void printForward(nodePointer head) {
    nodePointer iterator = head->lLink;
    for (; iterator != head; iterator = iterator->lLink) {
        printf("%5d", iterator->data);
    }
    printf("\n");
}
​
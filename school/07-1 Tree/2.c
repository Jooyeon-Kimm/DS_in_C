#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

#define MALLOC(p,s)\
    if (!((p) = malloc(s))) {\
    	fprintf(stderr, "Insufficient memory.");\
        exit(EXIT_FAILURE);\
    }

typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer leftChild, rightChild;
} node;

int front = 0, rear = 0;
treePointer queue[MAX_QUEUE_SIZE];



node* newNode(int data)
{
	treePointer temp;
	MALLOC(temp, sizeof(node));
	temp->data = data;
	temp->leftChild = temp->rightChild = NULL;
	return temp;
}

int queueEmpty() {
	printf("Queue is Empty");
	return 0;
}

int queueFull() {
	printf("Queue is Full");
	return 0;
}

void addq(treePointer node)
{
	queue[++rear] = node;
}

treePointer deleteq()
{
	return queue[++front];
}

void levelOrder(treePointer ptr){	
	if (!ptr) return; // emptry tree
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr) {
			printf("%d ", ptr->data);
			if (ptr->leftChild) addq(ptr->leftChild);
			if (ptr->rightChild) addq(ptr->rightChild);
		}
		else break;
	}
}

int main(void) {
	treePointer root;
	root = newNode(4);
	root->leftChild = newNode(3);
	root->rightChild = newNode(6);
	root->leftChild->leftChild = newNode(2);
	root->leftChild->rightChild = newNode(5);
	root->rightChild->rightChild = newNode(8);

	levelOrder(root);
}

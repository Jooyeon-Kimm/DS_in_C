#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

node* newNode(int data)
{
	treePointer temp;
	MALLOC(temp, sizeof(node));
	temp->data = data;
	temp->leftChild = temp->rightChild = NULL;
	return temp;
}

int main(void) {
	treePointer root;
	root = newNode(4);
	root->leftChild = newNode(3);
	root->rightChild = newNode(6);
	root->leftChild->leftChild = newNode(2);
	root->leftChild->rightChild = newNode(5);
	root->rightChild->rightChild = newNode(8);
	
	preorder(root);
}
​
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 24


int Temp[MAX_ELEMENTS];
int cnt = 0;

typedef struct element {
	int key;
} element;

typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftchild, rightchild;
};
treePointer root;

void insert(treePointer*, int);
treePointer modifiedSearch(treePointer p, int x);
void inorder(treePointer tree);

int main()
{
	element* status;
	int read;

	FILE* fp = fopen("in.txt", "r");
	if (fp == NULL) {
		perror("Error Opening File!");
		exit(1);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &read);
		insert(&root, read);
	}

	inorder(root);
	return 0;
}


void insert(treePointer* node, int k)
{
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node)) {
		ptr = (treePointer)malloc(sizeof(*ptr));
		ptr->data.key = k;
		ptr->leftchild = NULL; ptr->rightchild = NULL;
		if (*node)
			if (k < temp->data.key) temp->leftchild = ptr;
		// 여기서 temp는 부모이므로 ptr이 작은값으면 왼쪽으로
			else temp->rightchild = ptr; //ptr 큰 값이면 오른쪽으로
		else *node = ptr;
	}
}
treePointer modifiedSearch(treePointer root, int k) //삽입이 가능한지 탐색하여 가능여부를 반환
{
	treePointer temp = root;
	while (root)
	{
		temp = root;
		if (k < root->data.key) //삽입값이 작으면
			root = root->leftchild; //왼쪽으로 가서 다시 검색
		else if (k > root->data.key) //삽입값이 크면
			root = root->rightchild; // 오른쪽으로 가서 다시 검색
		else
			return NULL;
	}
	return temp; // parent 위치 반환
}
void inorder(treePointer tree)
{
	if (tree)
	{
		inorder(tree->leftchild);
		printf("%d ", tree->data.key);
		inorder(tree->rightchild);
	}
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200 /* maximum heap size+l */
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
	/* other fields */
} element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n)
{/* insert item into a max heap of current size *n */
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop(int* n)
{
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty! /n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
			child++;
		if (temp.key >= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

int main(void) {
	FILE* fp;
	fp = fopen("in.txt", "rt");
	int i, N, M, read;
	element item[MAX_ELEMENTS];
	int cnt = 0;
	if (fp == NULL) {
		perror("Error Opening File!");
		exit(1);
	}

	fscanf(fp, "%d", &N);
	printf("입력할 item 개수 >> %d\n", N);

	while(!feof(fp)) {
		fscanf(fp, "%d", &item[cnt]);
		push(item[cnt], &n);
		// printf("%d ", item[cnt]);
		cnt++;
	}

	printf("\n\npop 할 item 개수 >> ");
	scanf("%d", &M);

	for (i = 0; i < M; i++) {
		pop(&n);
	}

	for (int i = 1; i <= N- M; i++) {
		printf("%d ", heap[i]);
	}

	return 0;
}
​
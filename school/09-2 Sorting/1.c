#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100001
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

typedef struct element {
	int key;
}element;

void quickSort(element a[], int left, int right) {
	int pivot, i, j; element temp;
	if (left < right) {
		i = left; j = right + 1;
		pivot = a[left].key;
		do {
			do i++; while (a[i].key < pivot);
			do j--; while (a[j].key > pivot);
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j- 1);
		quickSort(a, j + 1, right);
	}
}

int main(void) {
	FILE* fp;
	fp = fopen("in.txt", "rt");
	if (fp == NULL) {
		perror("Error Opening File!");
		exit(1);
	}

	int idx = 0, i;
	element a[MAX];
	while (!feof(fp)) {
		fscanf(fp, "%d", &a[idx++]);

	}
	// printf("idx: %d\n", idx); idx: 정수 개수
	quickSort(a, 0, idx-1);

	for (i = 0; i < idx; i++) {
		printf("%d ", a[i]);
	}

}

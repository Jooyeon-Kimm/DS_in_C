#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int* x, int* y);
void sort(int list[], int n);

int main(void) {

	// 파일 생성
	FILE* pFile;
	pFile = fopen("data2.txt", "w+");


	// 데이터 개수
	int n, a;
	printf("Enter the number of numbers to generate: ");
	scanf_s("%d", &n);

	// 데이터 개수 유효성 검사
	if (n < 1) {
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}

	// 동적배열
	int* list = (int*)malloc(sizeof(int) * n);

	// 배열에 n개 정수 입력
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &a);
		list[i] = a;
		fprintf(pFile, "%d ", list[i]);
	}


	/* 배열 출력
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
	*/

	// selection sorting 
	sort(list, n);

	// sort값 출력
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}

}

void swap(int* x, int* y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void sort(int list[], int n) {
	int i, j, min, tmp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
		}

		swap(&list[i], &list[min]);
	}
}
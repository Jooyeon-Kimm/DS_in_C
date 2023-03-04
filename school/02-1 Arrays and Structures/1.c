// 행과 열의 크기를 로 입력 받는다 scanf
// 2차원 동적배열 생성 초기화 출력 메모리 해제는 각각 함수로 작성한다
// make2dArray (Program 2.3), init2dArray, print2dArray, free2dArray

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

#define MALLOC(p,s) \
	if (! ( (p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
	exit(EXIT_FAILURE); \
	}

#define CALLOC(p, n, s) \
	if (! ( (p) = calloc(n,s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

void add(int a[][MAX_SIZE], int b[][MAX_SIZE], int c[][MAX_SIZE], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
			c[i][k] = a[i][k] + b[i][k];
		}
	}
}

int** make2dArray(int rows, int cols) {
	int** x, i;
	MALLOC(x, rows * sizeof(*x));

	for (i = 0; i < rows; i++) {
		MALLOC(x[i], cols * sizeof(**x));
	}

	return x;
}



void init2dArray(int x[][MAX_SIZE], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
			int val;
			scanf("%d", &val);
			x[i][k] = val;
		}
	}
}


int print2dArray(int x[][MAX_SIZE], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
			printf("%d ", x[i][k]);
		} printf("\n");
	}
	return x;
}

void free2dArray(int x[][MAX_SIZE], int rows) {

	if (x != NULL) {
		for (int i = 0; i < rows; i++) {
			if (x[i] != NULL) {
				free(x[i]);
			}
		}
		free(x);
	}
}

int main(void) {
	int rows, cols, i, k, val;
	int** matrixA, ** matrixB, ** matrixC;

	printf("Enter row size and column size (ex) 3 4 :");
	scanf("%d %d", &rows, &cols);


	printf("matrix A\n");
	matrixA = make2dArray(rows, cols);
	init2dArray(matrixA, rows, cols);

	printf("matrix B\n");
	matrixB = make2dArray(rows, cols);
	init2dArray(matrixB, rows, cols);

	matrixC = make2dArray(rows, cols);
	add(matrixA, matrixB, matrixC, rows, cols);

	print2dArray(matrixC, rows, cols);


}
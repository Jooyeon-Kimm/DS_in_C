#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

#define MALLOC(p,s) \
	if (! ( (p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
	exit(EXIT_FAILURE); \
	}

int* makeArray(int size) {
	int* x, i;
	MALLOC(x, size * sizeof(*x));

	return x;
}

void initArray(int *ary, int size) {{
		for (int k = 0; k < size; k++) {
			scanf("%d", &ary[k]);
		}
	}
}

int findMin(int* ary, int size) {
	// int n = sizeof(ary) / sizeof(int);

	int min = ary[0];
	for (int i = 0; i < size; i++) {
		if (ary[i] < min) min = ary[i];
	}
	return min;
}

int main(void) {
	int n, min;
	int* arr;
    printf("배열 원소의 개수 n을 입력하세요: ");
	scanf("%d", &n);
    
	arr = makeArray(n);
	initArray(arr, n);
	
	min = findMin(arr, n);
    printf("min: %d\n", min);
    
	FILE* fp;
	fp = fopen("out.txt", "wt");
	fprintf(fp, "%d ", min);

}
​
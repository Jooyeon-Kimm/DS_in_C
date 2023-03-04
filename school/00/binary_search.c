#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) ( ((x)<(y)) ? -1 : ((x) = (y) ? 0 : 1) )
void swap(int* x, int* y);
void sort(int list[], int n);
int binsearch(int list[], int n, int searchnum);

int main(void) {

	// 파일 생성
	FILE* pFile, *qFile;
	pFile = fopen("data2.txt", "w+");

	// 데이터 개수
	int n, a, searchnum;
	char filename[30];
	printf("Enter the number of numbers to generate: ");
	scanf("%d", &n);

	// 데이터 개수 유효성 검사
	if (n < 1) {
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}

	// 동적배열
	int* list = (int*)malloc(sizeof(int) * n);

	// 배열에 n개 정수 입력
	for (int i = 0; i < n; i++) {
        printf("Enter the number (%d): ", i+1);
		scanf("%d", &a);
		list[i] = a;
		fprintf(pFile, "%d ", list[i]);
	}


	// selection sorting 
	sort(list, n);

	// 입력 (파일이름, 검색값)
	printf("파일이름: ");
	scanf("%s", filename);
	printf("검색값: ");
	scanf(" %d", &searchnum);
	
	// 입력한 파일 쓰기+모드로 열기
	qFile = fopen(filename, "w+");
    
	// 이진검색
	int result = binsearch(list, n, searchnum);


	// 결과 (터미널)
	if (result == -1) {
		printf("F (-1)\n");
		fprintf(qFile, "F (-1)\n");

	}
	
	else {
		printf("S (%d)\n", result);
        fprintf(qFile, "%d\n", result);
	}




}

binsearch(int list[], int n, int searchnum) {
	int low, high;
	int mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (searchnum == list[mid]) {            //탐색 성공
			return mid;
		}
		else if (searchnum < list[mid]) {        //탐색 범위를 아래쪽으로
			high = mid - 1;
		}
		else if (searchnum > list[mid]) {        //탐색 범위를 위쪽으로
			low = mid + 1;
		}
	}
	return -1;                            //탐색 실패
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
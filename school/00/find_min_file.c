# define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	// 파일 생성
	FILE* pFile;
	pFile = fopen("data1.txt", "w+");

	// 데이터 개수
	int n, min = 1000001, max = -1000001, num;
	printf("Enter the number of numbers to generate: ");
	scanf_s("%d", &n);

	// 데이터 개수 유효성 검사
	if (n < 1) {
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}

	// 파일에 n개 정수 입력
	fprintf(pFile, "%d", n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &num);
		fprintf(pFile, "%d ", num);

		if (num < min)
			min = num;
	}



	// min값 출력
	printf("%d", min);

	// 파일 닫기
	fclose(pFile);

}

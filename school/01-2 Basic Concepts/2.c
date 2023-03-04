#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // boolean

int prime(int x, int y);


int main(void) {
	char filename[10];
	int read[3], idx = 0;


	printf("파일 이름을 입력하세요: ");
	scanf("%s", filename);

	FILE* fp = fopen(filename, "rt");

	// 파일 열기 실패
	if (fp == NULL) {
		perror("Error opening file");
	}

	// 파일 열기 성공, 파일 읽기
	while (!feof(fp)) {
		fscanf(fp, "%d", &read[idx++]);
	}

	printf("read[0] = %d\n", read[0]);
	printf("read[1] = %d\n", read[1]);

	// x와 y가 서로소인지 판별
	int result = prime(read[0], read[1]);
	if (result == 1) printf("true\n");
	else printf("false\n");

}



int prime(int x, int y) {
	if (x == 1) return 1;
	if (y == 1) return 1;
	if (x != 1 && y != 1) {
		if (x == y) return 0;
		if (x < y) return prime(x, y - x);
		if (x > y ) return prime(x - y, y);
	}
}

/*
int prime(int x, int y) {
	if (y == 1)
		return 1;
	else if (x % y == 0)
		return 0;
	else
		return prime(x, y - 1);
}
*/
​
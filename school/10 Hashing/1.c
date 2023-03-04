#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct hash {
	int key;
	int abc[4];
} hash;

hash HASH[MAX] = { 0, };

int main(void) {

	FILE* f1, * f2;
	f1 = fopen("in.txt", "rt");
	f2 = fopen("search.txt", "rt");

	int D; // size of hash table
	printf("Input D >> ");
	scanf("%d", &D);

	if ((f1 == NULL) || (f2 == NULL)) {
		perror("Error Opening File!\n");
		exit(1);
	}

	// in.txt 읽기
	char read[MAX][4];
	int idx = 0;
	while (!feof(f1)) {
		fscanf(f1, "%s", read[idx++]);
	}

	int sum = 0;
	int i, k; // 반복
	
	// hash table에 값 삽입
	for (i = 0; i < idx; i++) {
		// printf("%s\n", read[i]);
		for (k = 0; k < 3; k++) {
			sum += read[i][k];
		}
		
		int key = sum % D;
		HASH[key].key = sum;
		strcpy(HASH[key].abc, read[i]);

		sum = 0;
	}
	

	// search.txt 읽기
	idx = 0;
	while (!feof(f2)) {
		fscanf(f2, "%s", read[idx++]);
	}

	for (i = 0; i < idx; i++) {
		for (k = 0; k < 3; k++) {
			sum += read[i][k];
		}

		int key = sum % D;
		if ((HASH[key].key == sum) && (strcmp(HASH[key].abc, read[i]) == 0)) {
			printf("S\n");
		}
		else printf("E\n");
		
		sum = 0;
	} puts("\n\n");

	for (i = 0; i < D; i++) {
		if (HASH[i].key == 0) {
			printf("%d:\n", i);
		}
		else {
			printf("%d: %s (%d) \n", i, HASH[i].abc, HASH[i].key);
		}
	}

	return 0;
}
​
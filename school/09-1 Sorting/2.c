#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p,s)\
    if (!((p) = malloc(s))) {\
    	fprintf(stderr, "Insufficient memory.");\
        exit(EXIT_FAILURE);\
    }

typedef struct person {
	int key;
	char name[5];
	int grade;
}person;

void insert(person e, person a[], int i)
{/* insert e into a[1:i]
such that a[1:i+1] is also ordered */
	a[0] = e;
	while (e.key < a[i].key) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

void insertionSort(person a[], int n)
{/* sort a[l:n] into nondecreasing order */
	int j;
	for (j = 2; j <= n; j++) {
		person temp = a[j];
		insert(temp, a, j - 1);
	}
}


int main(void) {
	int n;
	person* ppl;
	FILE* fp;
	fp = fopen("in1.txt", "rt");

	if (fp == NULL) {
		perror("Error Opening File!\n");
		exit(1);
	}

	fscanf(fp, "%d", &n);
	MALLOC(ppl, sizeof(person*) * (n + 2));
	printf("n: %d\n", n);


	for (int i = 1; i <= n; i++) {
		fscanf(fp, "%d %s %d", &(ppl[i].key), &(ppl[i].name), &(ppl[i].grade));
		printf("[%d] key: %d name: %s grade: %d\n", i, ppl[i].key, ppl[i].name, ppl[i].grade);

	}

	insertionSort(ppl, n);

	printf("\n\nResult of Insert Sort:\n");
	for (int i = 1; i <= n; i++) {
		printf("[%d] key: %d name: %s grade: %d\n", i, ppl[i].key, ppl[i].name, ppl[i].grade);

	}

	free(ppl);
	fclose(fp);
}
​
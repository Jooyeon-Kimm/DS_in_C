#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100


typedef struct node* nodePointer;
typedef struct node {
	int key;
	char abc[4];
	nodePointer next;
}node;

nodePointer HASH[MAX];


char search(int i, int read[][4]) {
	if ( strcmp(HASH[i]->abc, read[i]) ==0) {
		return 'S';
	}
	else {
		nodePointer current = HASH[i];
		while (current->next){
			if ((strcmp(current->next->abc, read[i]) == 0)) {
				return 'S';
			}
			current = current->next;
		}
	}
	return 'E';
}


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

		nodePointer addNode;
		addNode = (nodePointer)malloc(sizeof(node));

		addNode->key = sum;
		strcpy(addNode->abc, read[i]);


		int key = sum % D;
		addNode->next = HASH[key];
		HASH[key] = addNode;
		sum = 0;

		// printf("HASH[%d]: %d %s\n", key, HASH[key]->key, HASH[key]->abc);
	}

	// search.txt 읽기
	idx = 0;
	while (!feof(f2)) {
		fscanf(f2, "%s", read[idx++]);
	}

	char result;

	for (i = 0; i < idx; i++) {
		for (k = 0; k < 3; k++) {
			sum += read[i][k];
		}
		// printf("%s (%d)\n", read[i], sum);

		
		result = search(i, read[i]);
		if (result == 'S') printf("S\n");
		else if (result == 'E') printf("E\n");
		

		sum = 0;
	}puts("\n\n");

	for (int i = 0; i < D; i++)
	{
		printf("%d: ", i);
		if (HASH[i] != NULL)
		{
			nodePointer current = HASH[i];
			while (current->next)
			{
				printf(" %s (%d) ", current->abc, current->key);
				current = current->next;
			}
			printf(" %s (%d) \n", current->abc, current->key);
		}
	}




	return 0;
}
​
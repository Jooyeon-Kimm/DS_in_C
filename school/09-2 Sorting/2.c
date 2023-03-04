#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100001

typedef struct element {
	int key;
}element;



int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main(void) {
	FILE* fi, *fo;
	fi = fopen("in.txt", "rt");
	fo = fopen("out.txt", "wt");
	if (fi == NULL) {
		perror("Error Opening File!");
		exit(1);
	}

	int idx = 0, i;
	element a[MAX];
	while (!feof(fi)) {
		fscanf(fi, "%d", &a[idx++]);
	}
	
    printf("Before sorting the list: \n");
    for (i = 0; i < idx; i++) {
        printf("%d ", a[i]);
	} printf("\n");

    qsort(a, idx, sizeof(int), cmpfunc);

    printf("\nAfter sorting the list: \n");
    for (i = 0; i < idx; i++) {
        printf("%d ", a[i]);
		fprintf(fo, "%d ", a[i]);
    }


	return 0;

}
​
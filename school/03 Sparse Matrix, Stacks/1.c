#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_COL 11 /* maximum number of terms +1*/
typedef struct {
	int col;
	int row;
	int value;
} term;
term a[MAX_COL];
term b[MAX_COL];

void fasttranspose(term a[], term b[]);
void printMatrix(term a[], int rows, int cols, int value);
    

int main(void) {
	char filename[10];
	int read[MAX_COL], idx = 0;
    
	scanf("%s", filename);
	FILE* fp = fopen(filename, "rt");

	// 파일 열기 실패
	if (fp == NULL) {
		perror("Error opening file");
	}
   
    
    while(!feof(fp)) {
        fscanf(fp, "%d %d %d", &a[idx].row, &a[idx].col, &a[idx].value);
        idx++;
    }
    
    int rows = a[0].row;
    int cols = a[0].col;
    int value = a[0].value;
    fasttranspose(a, b);
    
    printf("A:\n");
    printMatrix(a, rows, cols, value);
	printf("B:\n");
    printMatrix(b, rows, cols, value);
    
    FILE* fpp = fopen("b.txt", "wt");
    
    for (int i=0; i<value; i++) {
        fprintf(fpp, "%d %d %d\n", b[i].row, b[i].col, b[i].value);
    }
    
    fclose(fp);
    fclose(fpp);
}




void fasttranspose(term a[], term b[]) {
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols; b[0].col = a[0].row;
	b[0].value = numTerms;

	if (numTerms > 0) {
		for (i = 0; i < numCols; i++) rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++) rowTerms[a[i].col]++;
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col; b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

void printMatrix(term a[], int rows, int cols, int value){
    int i, k;
    int matrix[MAX_COL][MAX_COL] = {0, };
    
    for (i = 1; i < value; i++ ){
       matrix[a[i].row][a[i].col] = a[i].value;
    }
    
    for (i = 0; i < rows; i++ ){
        for (k = 0; k < cols; k++ ) {
            printf("%4d ", matrix[i][k]);
        } puts("");
    }
}
​
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<string.h> // strcmp
void intersection(int a[], int b[], int aLength, int bLength, int result[], int *resultSize);
void ClearLineFromReadBuffer(void){    while(getchar() != '\n');}


int main(void) {

	// 파일이름 입력
	FILE *f1;
    char filename1[10];
    printf("파일1 이름 입력: ");
    scanf(" %s", filename1);
	f1 = fopen(filename1, "r");
 	// ClearLineFromReadBuffer();
    
    FILE *f2;
    char filename2[10];
    printf("파일2 이름 입력: ");
    scanf("%s", filename2);
	f2 = fopen(filename2, "r");
	// ClearLineFromReadBuffer();
    
    // 파일 길이 length와 현재 읽는 값이 넣어지는 위치 index
	int index1 = 0, index2 = 0;
    int length1 = 10, length2 = 10;
    
    // 파일내용 읽어오는 배열 read
	int * read1 = (int*)malloc(sizeof(int) * 10);
    int * read2 = (int*)malloc(sizeof(int) * 10);
    

    
	// 파일1 열기 실패
	if (f1 == NULL)
		perror("Error opening file");

    

	// 파일1 열기 성공
     do {
        if (index1 >= length1){
             length1 += 10;
        	read1 = (int*) realloc(read1, sizeof(int)*length1);
        }
     
        // printf("length1 =  %d, read1[%d] = %d\n", length1, index1, read1[index1]);
	} while (!feof(f1) && fscanf(f1, "%d", &read1[index1++]) == 1);


	// 파일1 화면에 출력
    printf("파일1: ");
	for (int i = 0; i < index1; i++) {
		printf("%d ", read1[i]);
	}
    printf("\n");


// 파일2 열기 실패
	if (f2 == NULL)
		perror("Error opening file");

    

	// 파일2 열기 성공
     do {
        if (index2 >= length2){
             length2 += 10;
        	read2 = (int*) realloc(read2, sizeof(int)*length2);
        }
     
        // printf("length2 =  %d, read2[%d] = %d\n", length2, index2, read2[index2]);
	} while (!feof(f2) && fscanf(f2, "%d", &read2[index2++]) == 1);


	// 파일2 화면에 출력
    printf("파일2: ");
	for (int i = 0; i < index2; i++) {
		printf("%d ", read2[i]);
	}
    printf("\n");

    
    // 교집합
    int longerLength = (length1 > length2) ? length1 : length2;
    int * result = (int*)malloc(sizeof(int) * longerLength);
    int resultSize = 0;
    
    intersection(read1, read2, index1, index2, result, &resultSize);
    printf("%s과 %s에 포함된 정수들의 교집합: ", filename1, filename2);
    for(int i=0; i<resultSize; i++){
        printf("%d ", result[i]);
    }
    printf("\n");
    
    
    free(read1);
    free(read2);

    fclose(f1);
    fclose(f2);


}


void intersection(int a[], int b[], int aLength, int bLength, int result[], int *resultSize)
{
    // a 인덱스: i, b 인덱스: k
    int k = 0;
	for (int i = 0; i < aLength && k < bLength; ) {
        
        if (a[i] == b[k]) {
            result[(*resultSize)++] = a[i];
            i++;
        	k++;
        }
        
        else if (a[i] > b[k]) {
            	k++;
         }
            
        else if (a[i] < b[k]) {
            i++;
        }                   
	}
    
}
​
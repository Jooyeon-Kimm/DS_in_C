#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h> // strcmp

char sequentialSearch(char list[][4], char find[], int length);
char iterbinsearch(char list[][4], char find[], int left, int right);
char recbinsearch(char list[][4], char find[], int left, int right);

int main(void) {

	// 파일이름 입력
	FILE* fp;
	char filename[10];
	printf("파일이름: ");
	scanf("%s", filename);
	fp = fopen(filename, "r");

	// 파일 안 알파벳 문자열 개수
	int length = 0;
	char read[100][4];


	// 파일 열기 실패
	if (fp == NULL)
		perror("Error opening file");

	// 파일 열기 성공
	do {
		fscanf(fp, "%s", read[length++]);
	} while (!feof(fp));

    /*
	// 파일 화면에 출력
	for (int i = 0; i < length; i++) {
		printf("%s\n", read[i]);
	}

	*/
	// 검색 단어 입력
	printf("검색단어 입력: ");
	char find[4];
	scanf("%s", find);


	// Sequential Search
	printf("Sequential search result: %c\n", sequentialSearch(read, find, length));

	// Iterative binary search
	printf("Iterative binary search result: %c\n", iterbinsearch(read, find, 0, length));

	// Recursive binary search
	printf("Recursive binary search result: %c\n", recbinsearch(read, find, 0, length));

	// 결과 (터미널)


	fclose(fp);


}
// Sequential Search
char sequentialSearch(char list[][4], char find[], int length)
{

	for (int i = 0; i < length; i++) {
		if (!strcmp(list[i], find)) {
			return 'S';
		}
	}
	return 'F';
}

// Program 1.7 Iterative Binary Search
char iterbinsearch(char list[][4], char find[], int left, int right)
{
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		
		int compare = strcmp(list[middle], find);
		
		if (compare == 0) {
			return 'S';
		}

		else if (compare > 0) {
			right = middle - 1;
		}

		else if (compare < 0) {
			left = middle + 1;
		}

    }
    return 'F';
}

// Program 1.8 Recursive Binary Search
char recbinsearch(char list[][4], char find[], int left, int right) 
{
	int middle;

	if (left <= right) {
		middle = (left + right) / 2;
		int compare = strcmp(list[middle], find);
        
		if (compare == 0) {
			return 'S';
		}

		else if (compare > 0) {
			recbinsearch(list, find, left, middle - 1);
		}

		else if (compare < 0) {
			recbinsearch(list, find, middle + 1, right);
		}

	}
	return 'F';
}

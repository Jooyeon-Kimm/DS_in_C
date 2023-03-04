#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct record {
	int X;
	int Y;
	int Z;
} record;
record R[MAX_SIZE];
//인덱스 1부터 값 넣음

void IterativeMergeSort(record R[], int n);
void mergePass(record initList[], record mergedList[], int n, int s);
void merge(record initList[], record mergedList[], int i, int m, int n);
int choose(record initList[], int i);
char XYZ='S';

int main()
{
	FILE* f = fopen("in.txt", "r");

	int n = 0;
	while (!feof(f))
		fscanf(f, "%d %d %d",
			&R[++n].X, &R[n].Y, &R[n].Z);
	fclose(f);

	printf("(scanf) : ");
	scanf("%c", &XYZ);

	IterativeMergeSort(R, n);

	FILE* f2 = fopen("out.txt", "w");
	for (int i = 1; i <= n; i++)
		fprintf(f2,"%d %d %d\n", R[i].X, R[i].Y, R[i].Z);

	fclose(f2);
	return 0;
}

void IterativeMergeSort(record R[], int n)
{
	int s = 1;
	record extra[MAX_SIZE];

	while (s < n)
	{
		mergePass(R, extra, n, s);
		s *= 2;
		mergePass(extra, R, n, s);
		s *= 2;
	}
}

void mergePass(record initList[], record mergedList[], int n, int s)
{
	int i;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);

	if ((i + s - 1) < n)
		merge(initList, mergedList, i, i + s - 1, n);
	else
		for (int j = i; j <= n; j++)
			mergedList[j] = initList[j];
}

void merge(record initList[], record mergedList[], int i, int m, int n)
{
	int j, k, t;
	j = m + 1;
	k = i;

	int field1, field2;

	while (i <= m && j <= n)
	{
		if ((field1 = choose(initList, i)) <= (field2 = choose(initList, j)))
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}

	if (i > m)
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	else
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
}

int choose(record initList[], int i)
{
	int field;
	if (XYZ == 'X')
		field = initList[i].X;
	else if (XYZ == 'Y')
		field = initList[i].Y;
	else if (XYZ == 'Z')
		field = initList[i].Z;

	return field;
}
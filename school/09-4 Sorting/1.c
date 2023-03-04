#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define SWAP(x,y,z) (z=x,x=y,y=z)

typedef struct element {
	int key;
} element;

element a[MAX_SIZE];

void heapSort(element a[], int n);
void adjust(element list[], int root, int n);

int main()
{
	FILE* f = fopen("in.txt", "r");

	int n = 0;
	while (!feof(f))
		fscanf(f, "%d", &a[++n].key);
	fclose(f);

	heapSort(a, n);

	FILE* f2 = fopen("out.txt", "w");
	for (int i = n; i >= 1; i--)
		fprintf(f2,"%d ", a[i].key);
	fclose(f2);

	return 0;
}


void heapSort(element a[], int n)
{
	int i, j;
	element temp;
	for (i = n - 1; i > 0; i--)
		adjust(a, i, n);
	for (i = n - 1; i > 0; i--)
	{
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i);
	}
}
void adjust(element list[], int root, int n)
{
	int child, rootkey;
	element temp;
	temp = list[root];
	rootkey = list[root].key;
	child = 2 * root;
	while (child <= n)
	{
		if ((child < n) && (list[child].key < list[child + 1].key))
			child++;
		if (rootkey > list[child].key)
			break;
		else
		{
			list[child / 2] = list[child];
			child *= 2;
		}
	}
	list[child / 2] = temp;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100

typedef struct element {
	int key;
} element;
element a[MAX_SIZE];

int link[MAX_SIZE];

int radixSort(element a[], int link[], int d, int r, int n);
int digit(element an, int i, int r);

int d = 2;
int r = 10;
int main()
{
	FILE* f = fopen("in.txt", "r");

	int n = 0;
	while (!feof(f))
		fscanf(f, "%d", &a[++n].key);
	fclose(f);

	int first= radixSort(a, link, d, r, n);

	FILE* f2 = fopen("out.txt", "w");
	while (first)
	{
		fprintf(f2,"%d ", a[first]);
		first = link[first];
	}
	fclose(f2);
	return 0;
}


int radixSort(element a[], int link[], int d, int r, int n)
{
	int front[10];
	int rear[10];
	int i, bin, current, first, last;
	first = 1;
	for (i = 1; i < n; i++)
		link[i] = i + 1;
	link[n] = 0;
	for (i = d - 1; i >= 0; i--)
	{
		for (bin = 0; bin < r; bin++)
			front[bin] = 0;
		for (current = first; current; current = link[current])
		{
			bin = digit(a[current], i, r);//a[current]는 일반화시키면 element an;
			if (front[bin] == 0)
				front[bin] = current;
			else link[rear[bin]] = current;
			rear[bin] = current;
		}
		for (bin = 0; !front[bin]; bin++);//여기끝에 ;를 적네?
		first = front[bin]; last = rear[bin];
		for (bin++;bin<r;bin++)
			if (front[bin])
			{
				link[last] = front[bin];
				last = rear[bin];
			}
		link[last] = 0;
	}
	first= link[front[0]];//추가해줌
	//시작값의 인덱스는 front[0]이 아니라 front[0]의 다음 link 값
	return first;
}

int digit(element an, int i, int r)
{//179=1*100+7*10+9*1 임을 이용
 //지수승을 계산하기 위해선 ^로는 안됨
 //#include <math.h>를 해주고 pow함수를 이용해주어야하는데
 //pow함수는 double형에 대해 계산해주므로 
 //pow의 인수로 넣을 땐 double로, pow의 결과값은 int로 변환해주어야함
	int temp;
	int number = an.key;
	for (int ii = 0; ii <= i; ii++)
	{
		temp = number / ((int)pow((double)r, (double)(d - ii - 1)));
		number = number - temp * ((int)pow((double)r, (double)(d - ii - 1)));
	}
	return temp;
}
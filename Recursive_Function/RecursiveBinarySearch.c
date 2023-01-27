#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// Recursive Binary Search Function
// Can only be used when all the data is sorted
// ����� ����Ž�� �Լ�
// ��� �����Ͱ� ���ĵǾ��� �� ���� �� �ִ�
int RBS(int arr[], int first, int last, int target)
{
	int middle = (first + last) / 2;

	if (first > last)	// failed searching, Ž�� ����
	{
		return -1;
	}

	if (arr[middle] == target)	// Ž�� ����
	{
		return middle;
	}

	else if (target > arr[middle]) // ã�� ���� �߰��� ������ Ŭ ��
	{
		return RBS(arr, middle + 1, last, target);
	}

	else // target < arr[middle]
	{
		return RBS(arr, first, middle - 1, target);
	}
}

int main(void)
{
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	int arr_len = sizeof(arr) / sizeof(int);


	printf("Find the index of 7 :");
	printf("%d\n", RBS(arr, 0, arr_len - 1, 7));

	printf("Find the index of 19 :");
	printf("%d\n", RBS(arr, 0, arr_len - 1, 19));
}
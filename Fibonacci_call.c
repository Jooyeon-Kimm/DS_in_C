#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// Fibonacci �Լ��� ȣ�� ������ ����ؼ� ����
// Print out and view the calling order of the Fibonacci function
int Fibonacci(int i)
{
	printf("Function Call Parameter %d\n", i);
	if (i == 0) return 0;
	if (i == 1) return 1;
	return Fibonacci(i - 1) + Fibonacci(i - 2);
}

int main(void)
{
	Fibonacci(4);
}
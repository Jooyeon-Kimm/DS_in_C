#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Fibonacci(int i)
{
	if (i == 0) return 0;
	if (i == 1) return 1;
	return Fibonacci(i - 1) + Fibonacci(i - 2);
}

int main(void)
{
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", Fibonacci(i));
	}
}
// 프로그램이 수행될 수 있는 N의 최대값: 46
// Fibo(47) 이 INT_MAX 범위를 넘어가서
// 오버플로우 발생

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

int iFibo(int n);
int rFibo(int n);

int main(void) {

	int n;
	clock_t start;
	double duration;
	long repetitions = 0;

	printf("n을 입력하세요: ");
	scanf("%d", &n);
	printf("\n");

	// iFibo
	start = clock();
	do {
		repetitions++;
		iFibo(n);
	} while (clock() - start < 0.000000000000000000000000001);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	printf("Iterative F(%d) = %d\n", n, iFibo(n));
	printf("F(%d) Iterative Time = %lf\n", n, duration);
	printf("\n");

	// rFibo
	start = clock();
	do {
		repetitions++;
		rFibo(n);
	} while (clock() - start < 0.00000000000000000000001);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;	
	duration /= repetitions;
	printf("Recursive F(%d) = %d\n", n, rFibo(n));
	printf("F(%d) Recursive Time = %lf\n", n, duration);

	
	
}

int iFibo(int n) {
	int f0 = 0, f1 = 1, fi;

	if (n <= 1) {
		return n;
	}
	else {
		for (int i = 2; i <= n; i++) {
			fi = f0 + f1;
			f0 = f1;
			f1 = fi;
		}
		return fi;
	}
}

int rFibo(int n) {
	if (n <= 1) {
		return n;
	}

	else {
		return rFibo(n - 1) + rFibo(n - 2);
	}
}
​
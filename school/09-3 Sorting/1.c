#define _CRT_SECURE_NO_WARNINGS
#include stdio.h
#define SWAP(a, b,tmp) {(tmp)=(a); (a)=(b); (b)=(tmp);}
#define MAX 100

int heapSort(int heap[], int number) {
	 힙을 구성할 때, 
	 부모노드가 자식노드보다 작도록 구성
	for (int i = 0; i  number; i++) {
		int c = i;
		do {
			int root = (c - 1)  2;
			if (heap[root]  heap[c]) {
				int temp = heap[root];
				heap[root] = heap[c];
				heap[c] = temp;
			}
			c = root;
		} while (c != 0);

		 크기를 줄여가며 반복적으로 힙을 구성
		for (int i = number - 1; i = 0; i--) {
			int temp = heap[0];
			heap[0] = heap[i];
			heap[i] = temp;

			int root = 0;
			int c = 1;

			do {
				c = 2  root + 1;

				 자식 중에 더 작은 값을 찾기
				if (c  i - 1 && heap[c]  heap[c + 1])
					c++;
				 부모가 자식보다 크면 교환
				if (c  i && heap[root]  heap[c]) {
					temp = heap[root];
					heap[root] = heap[c];
					heap[c] = temp;
				}
				root = c;
			} while (c  i);

		}

	}
	 결과 출력
	for (int i = 0; i  number; i++) {
		printf(%d , heap[i]);
	}printf(n);
}


int main(void) {
	int read[MAX], idx = 0;
	int i = 1;

	FILE fi,  fo;
	fi = fopen(in.txt, rt);
	fo = fopen(out.txt, wt);

	if (fi == NULL) {
		perror(Error Opening File!);
	}
	while (!feof(fi)) {
		fscanf(fi, %d, &read[idx++]);
	}

	printf(힙 정렬 전 );
	for (int i = 0; i  9; i++) {
		printf(%d , read[i]);
	}

	printf(n힙 정렬 후 );
	heapSort(read, idx);
	for (i = 0; i  idx; i++) {
		fprintf(fo, %d , read[i]);
	}

}
​
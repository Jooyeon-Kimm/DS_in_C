
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if(!((p)=malloc(s))){fprintf(stderr,"메모리 부족\n");exit(1);}
#define CALLOC(p,n,s) if(!((p)=calloc(n,s))){fprintf(stderr,"메모리 부족\n");exit(1);}
#define MAX_SIZE 10

typedef struct adjlist* listPointer;
typedef struct adjlist {
	int data;
	listPointer link;
}adjlist;


listPointer newlist(int n)
{
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->link = NULL;
	temp->data = n;

	return temp;
}

void insert(listPointer first,listPointer x)
{
	listPointer temp;
	temp = first;

	while (1)
	{
		if (temp->link == NULL)
		{
			temp->link = x;
			break;
		}
		temp = temp->link;
	}
}
void printList(listPointer first,int num)
{
	listPointer temp;
	printf("Vertex %d :", num);
	for (temp=first->link;temp ; temp = temp->link)
		printf("%3d", temp->data);
	printf("\n");
}
int main()
{
	FILE* f = fopen("in15.txt", "r");
	if (f == NULL)
	{
		printf("파일 읽기 실패\n"); exit(1);
	}

	int n,i,j;  
	int** m;
	listPointer* list;

	fscanf(f, "%d", &n);

	MALLOC(m, n * sizeof(*m)); // adjacency matrix동적 할당
	MALLOC(list, n *sizeof(*list)); // adjacency list 동적 할당
	for (i = 0; i < n; i++)
	{
		CALLOC(m[i], n , sizeof(**m));  // adjacency matrix 를 0으로 초기화
		MALLOC(list[i], sizeof(*list));
		list[i]->link= NULL;
	}
	listPointer x;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			fscanf(f, "%d", &m[i][j]);
			m[j][i] = m[i][j];//adjacency list에 데이터 삽입
		}
	}

	for (i = 0; i < n; i++)
	{
		for(j=0;j<n;j++)
			if (m[i][j] == 1 || m[j][i] == 1) // data 가 1일 때, 노드 생성 후 삽입
			{
				x = newlist(j);
				insert(list[i], x);
			}
	}


	for (i = 0; i < n; i++)
	{
		printList(list[i], i);
	}

	fclose(f);
	return 0;
}
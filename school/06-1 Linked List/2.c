#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#define IS_EMPTY( first ) ( !(first) )

#define MALLOC(p,s) \
if (! ( (p) = malloc (s) ) ) { \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE);\
}

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

void insert(listPointer* first, listPointer x, int in)
{
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = in;

	if (*first) {
		temp->link = x->link;
		x->link = temp;
	}
	else {
		temp->link = NULL;
		*first = temp;
	}
}

/*
void delete(listPointer* first, listPointer trail, listPointer x)
{
	if (trail) {
		trail->link = x->link;
    }
    
	else //  delete the 1st node
		*first = (*first)->link;
	free(x);

}
*/

void sortedInsert(listPointer* head, listPointer newNode)
{
	listNode dummy;
	listPointer current = &dummy;
	dummy.link = *head;

	while (current->link != NULL && current->link->data < newNode->data) {
		current = current->link;
	}

	newNode->link = current->link;
	current->link = newNode;
	*head = dummy.link;
}


void insertSort(listPointer* head)
{
	listPointer result = NULL;
	listPointer current = *head;
	listPointer next;

	while (current != NULL) {
		next = current->link;

		sortedInsert(&result, current);
		current = next;
	}

	*head = result;
}


int exist(listPointer first, int toFind) {
    listPointer node;
    int cnt = 0;
    
    for (; first; first = first -> link) {
        cnt++;
        if (first->data == toFind) return cnt;

    }
     return 0;
}

void printList(listPointer first)
{
	// printf("The list contains: ");
	first = first->link; // 쓰레기값 출력 없애기
	for (; first; first = first->link) {
		printf("%4d", first->data);
	}
	printf("\n ");
}

listNode *Search(listPointer first, int x)
{
	listNode *p;
	p = first;

	while( p != NULL ) {
		if( p->data == x ) return p; 
		p = p->link;
	}

	return p; // 없다면 그냥 p,  NULL 반환
}

//특정 data 가 들어있는 listNode 를 삭제하는 함수입니다.
void DeleteNodeData(listPointer *first, int DeleteData)
{
	listPointer p = *first;
	listPointer removed;
	int count;
	
    removed = Search(*first, DeleteData); 
	// search 함수를 참고 하는 부분. 지워질 node 를 removed 가 가리킵니다.

	if( p == removed ) // 지워질 node 가 첫번째 일때.
		*first = p->link;
	else {
		while( p->link != removed ) 
			p = p->link;  // removed 전의 선행 노드를 찾아 p 가 가리킵니다.

		if ( removed->link == NULL) 
			p->link = NULL;  // 마지막 노드의 link 를 NULL 로 설정.
		else 
			p->link = removed->link; 

		free(removed); 
	}
}


int main(void) {
	int in;
	listPointer first = NULL;
	MALLOC(first, sizeof(*first));
	
	first->link = NULL;
    
	FILE* fp = fopen("in.txt", "rt");
	if (fp == NULL) {
		perror("Error Opening File.\n");
		exit(1);
	}


	while (!feof(fp)) {
		fscanf(fp, "%d", &in);
		insert(&first, first, in);
	}
	insertSort(&first);
	printList(first);
	
	
    
	while (1) {
		printf("\ninput item: ");
		scanf("%d", &in);
		if (in == -1) exit(1);
		

        int toDelete = exist(first, in);
        printf("delete: %d\n", toDelete);
        
        if(!toDelete){
		    insert(&first, first, in);
		    insertSort(&first);
		    printList(first);
        }
		
		else {
		    DeleteNodeData(&first, in);
        	insertSort(&first);
		    printList(first);
		}

	}
}
	
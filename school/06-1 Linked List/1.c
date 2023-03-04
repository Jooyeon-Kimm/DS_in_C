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

void delete(listPointer* first, listPointer trail, listPointer x)
{
	if (trail)
		trail->link = x->link;
	else
		*first = (*first)->link;
	free(x);
}

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

	while (current != NULL){
		next = current->link;

		sortedInsert(&result, current);
		current = next;
	}

	*head = result;
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


	while(1) {
		printf("\ninput item: ");
		scanf("%d", &in);
		if (in == -1) exit(1);

		insert(&first, first, in);
		insertSort(&first);
		printList(first);
		
		
	}
	// insert(&first, x, in);
	// delete(&first, NULL, x);

}

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define MALLOC(ptr, size){\
	if(!((ptr) = malloc(size))){\
		printf("Insufficient Memory!\n");\
		exit(EXIT_FAILURE);\
	}\
}
#define FOPEN(fptr, fname, mode){\
	if (!((fptr) = fopen(fname, mode))) {\
		printf("File doesn't Exist!\n");\
		exit(EXIT_FAILURE);\
	}\
}

typedef struct Node* NodePointer;
typedef struct Node {
	NodePointer Llink;
	NodePointer Rlink;
	int data;
} Node;

void InsertSequently(NodePointer head, int data);
void Insert(NodePointer* previousNode, int data);
void Delete(NodePointer head, int key);
void PrintList(NodePointer head);
int SequentialSearch(NodePointer head, int key);


int main() {
	FILE* file;
	NodePointer head, prev;

	MALLOC(head, sizeof(Node));
	head->Llink = head;
	head->Rlink = head;
	prev = head;

	int menu;
	while (1) {
		printf("작업 선택 (1. 입력 2. 추가 3. 검색 4. 삭제 5. 종료) >> ");
		scanf("%d", &menu);

		if (menu == 1) {
			char fileName[30];
			printf("파일 이름 입력 >> ");
			scanf("%s", fileName);
			FOPEN(file, fileName, "r");

			while (!feof(file)) {
				int element;
				fscanf(file, "%d", &element);
				Insert(&prev, element);
			}
			prev->Rlink = head;
			head->Llink = prev;

			PrintList(head);
		}
		else if (menu == 2) {
			int element;
			printf("데이터 입력 >> ");
			scanf("%d", &element);
			InsertSequently(head, element);
			PrintList(head);
		}
		else if (menu == 3) {
			int key;
			printf("검색 데이터 >> ");
			scanf("%d", &key);
			printf("%d\n", SequentialSearch(head, key));
			PrintList(head);
		}
		else if (menu == 4) {
			int key;
			printf("삭제 데이터 >> ");
			scanf("%d", &key);
			Delete(head, key);
		}
		else if (menu == 5) {
			break;
		}
	}

	return 0;
}

void InsertSequently(NodePointer head, int data) {
	NodePointer newNode;
	MALLOC(newNode, sizeof(Node));
	newNode->data = data;

	NodePointer iterator = head->Rlink;
	for (; iterator != head; iterator = iterator->Rlink) {
		if (iterator->Rlink != head) {
			if (iterator->data < data && data < iterator->Rlink->data) {
				newNode->Llink = iterator;
				newNode->Rlink = iterator->Rlink;
				iterator->Rlink->Llink = newNode;
				iterator->Rlink = newNode;
				break;
			}
		}
		else {
			iterator->Rlink = newNode;
			newNode->Llink = iterator;
			newNode->Rlink = head;
		}
	}
}

void Insert(NodePointer* previousNode, int data) {
	NodePointer newNode;
	MALLOC(newNode, sizeof(Node));
	newNode->data = data;

	(*previousNode)->Llink = newNode;
	newNode->Rlink = (*previousNode)->Rlink;
	(*previousNode)->Rlink->Llink = newNode;
	(*previousNode)->Rlink = newNode;

	(*previousNode) = newNode;
}

void Delete(NodePointer head, int key) {
	NodePointer previousNode = head->Rlink;
	for (; previousNode != head; previousNode = previousNode->Rlink) {
		if (previousNode->Rlink->data == key) {
			NodePointer toDelete = previousNode->Rlink;
			NodePointer nextNode = previousNode->Rlink->Rlink;

			previousNode->Rlink = nextNode;
			nextNode->Llink = previousNode;

			free(toDelete);
			PrintList(head);
			return;
		}
	}
	printf("Invaild!\n");
	
}

void PrintList(NodePointer head) {
	NodePointer iterator = head->Rlink;
	for (; iterator != head; iterator = iterator->Rlink) {
		printf("%d ", iterator->data);
	}
	printf("\n");
}

int SequentialSearch(NodePointer head, int key) {
	NodePointer iterator = head->Rlink;
	for (int index = 1; iterator != head; iterator = iterator->Rlink, index++) {
		if (iterator->data == key) return index;
	}
	return 0;
}
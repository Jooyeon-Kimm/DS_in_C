#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


//다항식 리스트의 노드 구조 정의
typedef struct Node {
    int coef; //계수
    int expo; //지수
    struct Node* link;
} Node;

typedef struct ListHead {
    Node* head;
} ListHead;

//공백 다항식 리스트 생성 연산
ListHead* createLinkedList(void) {
    ListHead* L;
    L = (ListHead*)malloc(sizeof(ListHead));
    L->head = NULL;
    return L;
}

//다항식 리스트에 마지막 노드 삽입 연산
void addLastNode(ListHead* L, int coef, int expo) {
    Node* newNode;
    Node* p;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->expo = expo;
    newNode->link = NULL;
    if (L->head == NULL) {
        L->head = newNode;
        return;
    }
    else {
        p = L->head;
        while (p->link != NULL) {
            p = p->link;
        }
        p->link = newNode;
    }
}

//두 다항식의 합을 구하는 연산
void addPoly(ListHead* A, ListHead* B, ListHead* C) {
    Node* pA = A->head;
    Node* pB = B->head;
    int sum;

    while (pA && pB) {
        if (pA->expo == pB->expo) {
            sum = pA->coef + pB->coef;
            addLastNode(C, sum, pA->expo);
            pA = pA->link; pB = pB->link;
        }
        else if (pA->expo > pB->expo) {
            addLastNode(C, pA->coef, pA->expo);
            pA = pA->link;
        }
        else {
            addLastNode(C, pB->coef, pB->expo);
            pB = pB->link;
        }
    }
    for (; pA != NULL; pA = pA->link)
        addLastNode(C, pA->coef, pA->expo);
    for (; pB != NULL; pB = pB->link)
        addLastNode(C, pB->coef, pB->expo);
}

//다항식 리스트를 출력하는 연산
void printPoly(ListHead* L) {
    Node* p = L->head;
    for (; p; p = p->link) {
        if (p->coef == 0) continue;
        printf("%d %d ", p->coef, p->expo);
    }
}

int main(void) {
    //리스트 노드 생성
    ListHead* A, * B, * C;
    //공백 다항식 리스트 A, B, C 생성
    A = createLinkedList();
    B = createLinkedList();
    C = createLinkedList();

    FILE* fp1, * fp2;
    fp1 = fopen("in1.txt", "rt");
    fp2 = fopen("in2.txt", "rt");

    if (fp1 == NULL || fp2 == NULL) {
        printf("File not found\n");
        exit(1);
    }
    
    int coef, expon;
    while (!feof(fp1)) {
        fscanf(fp1, "%d", &coef);
        fscanf(fp1, "%d", &expon);
        addLastNode(A, coef, expon);
    }

    while (!feof(fp2)) {
        fscanf(fp2, "%d", &coef);
        fscanf(fp2, "%d", &expon);
        addLastNode(B, coef, expon);
    }

    printf("A: ");
    printPoly(A);


    printf("\nB: ");
    printPoly(B);

    addPoly(A, B, C);
    printf("\nC: ");
    printPoly(C);

}
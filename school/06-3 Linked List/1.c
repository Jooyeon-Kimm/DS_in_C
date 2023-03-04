#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MALLOC(ptr, size)                                                      \
  {                                                                            \
    if (!((ptr) = malloc(size))) {                                             \
      fprintf(stderr, "Insufficient Memory");                                  \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  }

#define MAX_SIZE 50

typedef enum { head, entry } tagfield;
typedef struct matrixNode* matrixPointer;
typedef struct entryNode {
    int row, col, value;
} entryNode;
typedef struct matrixNode {
    matrixPointer down;
    matrixPointer right;
    tagfield tag;
    union {
        matrixPointer next;
        entryNode entry;
    } u;
} matrixNode;

matrixPointer hdnode[MAX_SIZE];
matrixPointer newNode();
matrixPointer mread();
void mwrite(matrixPointer node);
void merase(matrixPointer* node);

int main() {
    int menu = 0;
    matrixPointer node = NULL;

    while (1) {
        printf("matrix 작업 선택 (1. 입력, 2. 출력, 3. 삭제, 4. 종료) : ");
        scanf("%d", &menu);

        if (menu == 1) {
            node = mread();
        }
        else if (menu == 2) {
            mwrite(node);
        }
        else if (menu == 3) {
            merase(&node);
        }
        else if (menu == 4) {
            break;
        }
    }

    return 0;
}

matrixPointer newNode() { return (matrixPointer)malloc(sizeof(matrixNode)); }

matrixPointer mread() {
    int numRows, numCols, numTerms, numHeads;
    int row, col, value, currentRow;
    matrixPointer temp, last, node;

    printf("행과 열의 크기 및 nonzero 항의 수 입력\n");
    scanf("%d %d %d", &numRows, &numCols, &numTerms);

    numHeads = (numCols > numRows) ? numCols : numRows;

    node = newNode();
    node->u.entry.row = numRows;
    node->u.entry.col = numCols;

    if (!numHeads)
        node->right = node;
    else {
        for (int i = 0; i < numHeads; i++) {
            temp = newNode();
            hdnode[i] = temp;
            hdnode[i]->tag = head;
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
    }

    currentRow = 0;
    last = hdnode[0];

    printf("행, 열, 값 입력\n");
    for (int i = 0; i < numTerms; i++) {
        scanf("%d %d %d", &row, &col, &value);

        if (row > currentRow) {
            last->right = hdnode[currentRow];
            currentRow = row;
            last = hdnode[row];
        }
        temp = newNode();
        temp->tag = entry;
        temp->u.entry.row = row;
        temp->u.entry.col = col;
        temp->u.entry.value = value;

        last->right = temp;
        last = temp;

        hdnode[col]->u.next->down = temp;
        hdnode[col]->u.next = temp;
    }
    last->right = hdnode[currentRow];

    for (int i = 0; i < numCols; i++) {
        hdnode[i]->u.next->down = hdnode[i];
    }

    for (int i = 0; i < numHeads - 1; i++) {
        hdnode[i]->u.next = hdnode[i + 1];
        hdnode[numHeads - 1]->u.next = node;
        node->right = hdnode[0];
    }
    return node;
}

void mwrite(matrixPointer node) {
    matrixPointer temp, head = node->right;

    printf("\nnumRows = %d, numCols = %d\n", node->u.entry.row,
        node->u.entry.col);
    printf("The matrix by row, col and value \n\n");

    for (int i = 0; i < node->u.entry.row; i++) {
        for (temp = head->right; temp != head; temp = temp->right) {
            printf("%5d%5d%5d\n", temp->u.entry.row, temp->u.entry.col,
                temp->u.entry.value);
        }
        head = head->u.next;
    }
}

void merase(matrixPointer* node) {
    matrixPointer x, y, head = (*node)->right;
    for (int i = 0; i < (*node)->u.entry.row; i++) {
        y = head->right;
        while (y != head) {
            x = y;
            y = y->right;
            free(x);
        }
        x = head;
        head = head->u.next;
        free(x);
    }

    y = head;
    while (y != *node) {
        x = y;
        y = y->u.next;
        free(x);
    }
    free(*node);
    *node = NULL;
}
​
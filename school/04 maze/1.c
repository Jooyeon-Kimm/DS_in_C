#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100
#define MALLOC(p, s) \
if (!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
}

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[MAX_STACK_SIZE];
int top = -1;

typedef struct {
	short int vert;
	short int horiz;
} offsets;
offsets move[8];

void make_move();
int** make_maze(int row, int col);
int** make_mark(int row, int col);
void push(element item);
element pop();
void path();

int** maze;
int** mark;
int sizerow, sizecol;

int main() {

	FILE* f;
	char filename[10];
	scanf("%s", filename);
	if ((f = fopen(filename, "r")) == NULL)		// 파일 열기
	{
		printf("파일이 열리지 않습니다.\n");
		exit(1);
	}

	// maze 크기 읽어오기
	fscanf(f, "%d %d", &sizerow, &sizecol);

	// move, maze, mark 초기세팅 (maze 1로 초기화, mark는 겉만 1로 안은 0으로)
	maze = make_maze(sizerow, sizecol);
	mark = make_mark(sizerow, sizecol);
	make_move();

	// maze 정보 읽어오기
	for (int i = 1; i <= sizerow; i++) {
		for (int j = 1; j <= sizecol; j++)
			fscanf(f, "%d", &maze[i][j]);
	}

	// 길찾아 출력
	path();

	free(maze);
	free(mark);
	fclose(f);
}

void make_move()
{
	move[0].vert = -1, move[0].horiz = 0;
	move[1].vert = -1, move[1].horiz = 1;
	move[2].vert = 0, move[2].horiz = 1;
	move[3].vert = 1, move[3].horiz = 1;
	move[4].vert = 1, move[4].horiz = 0;
	move[5].vert = 1, move[5].horiz = -1;
	move[6].vert = 0, move[6].horiz = -1;
	move[7].vert = -1, move[7].horiz = -1;
}
int** make_maze(int row, int col)
{
	int** x;
	MALLOC(x, (row + 2) * sizeof(*x));

	for (int i = 0; i < row + 2; i++)
		MALLOC(x[i], (col + 2) * sizeof(**x));

	for (int i = 0; i < row + 2; i++) {
		for (int j = 0; j < col + 2; j++)
			x[i][j] = 1;
	}

	return x;
}
int** make_mark(int row, int col)
{
	int** x;
	MALLOC(x, (row + 2) * sizeof(*x));

	for (int i = 0; i < row + 2; i++)
		MALLOC(x[i], (col + 2) * sizeof(**x));

	for (int i = 0; i < row + 2; i++) {
		for (int j = 0; j < col + 2; j++)
			x[i][j] = 1;
	}

	for (int i = 1; i < row + 1; i++) {
		for (int j = 1; j < col + 1; j++)
			x[i][j] = 0;
	}

	return x;
}
void push(element item)
{
	stack[++top] = item;
}
element pop()			//?							
{
	return stack[top--];
}

void path()
{
	int i, row, col, nextRow, nextCol, dir;
	int found = false; //?
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;

	while (top > -1 && !found) {
		position = pop();			//?
		row = position.row; col = position.col; dir = position.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert; nextCol = col + move[dir].horiz;

			if (nextRow == sizerow && nextCol == sizecol)
				found = true;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col; position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else
				++dir;
		}
	}

	if (found) {
		printf("The path is:\n");
		printf("row  col\n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", sizerow, sizecol);
	}
	else
		printf("The maze does not have a path\n");
}
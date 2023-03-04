#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100 /* maximum stack size */
#define MAX_EXPR_SIZE 100 /* maximum stack size */


typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

char expr[MAX_EXPR_SIZE];
precedence stack[MAX_STACK_SIZE];
int top = 0; // stack_top

/* isp and icp arrays index is value of precedence
lparen, rparen , plus, minus, times, divide, mod, eos */
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void push(precedence item);
precedence pop();
void printToken(precedence token);
precedence getToken(char* symbol, int* n);
void postfix(void);

int main() {

	int idx = 0;
	char filename[10];
	scanf("%s", filename);
	FILE* fp = fopen(filename, "rt");

	if (fp == NULL) {
		perror("Error opening file.");
		exit(1);
	}

	while (!feof(fp)) {
		fscanf(fp, "%c", &expr[idx++]);
	}
	
	postfix();
	fclose(fp);
}

void push(precedence item) {
	if (top >= MAX_STACK_SIZE - 1) printf("stack is full\n");
	else stack[++top] = item;
}
precedence pop() {
	if (top == -1) printf("stack is empty");
	return stack[top--];
}

void printToken(precedence token) {
	switch (token) {
	case lparen: printf("( "); break;
	case rparen: printf(") "); break;
	case plus: printf("+ "); break;
	case minus: printf("- "); break;
	case divide: printf("/ "); break;
	case times: printf("* "); break;
	case mod: printf("%% "); break;
	case eos: printf("\0"); break;
	}

}

precedence getToken(char* symbol, int* n) // 연산자 혹은 피연산자를 구분하고 이를 token으로 할당하는 함수
{
	/* get the next token, symbol is the character representation, which is returned, the
	token is represented by its enumerated value, which is returned in the function name */
	switch (*(symbol + *n)) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand; /* no error checking, default is operand */
	}
}

void postfix(void) { /* output the postfix of the expression. The expression string, stack, and the top are global */
	int n = 0;
	precedence token;

	stack[0] = eos;
	// 먼저 문자열 중 첫 번째 문자를 pㅅrecedence로 입력 받는다.
	// 해당 반복문은 token이 eos가 나올 때까지 반복한다.
	for (token = getToken(expr, &n); token != eos; token = getToken(expr, &n)) {
		if (token == operand) // token이 피연산자이면 바로 출력
			printf("%c ", expr[n]);
		else if (token == rparen) { // token이 ')'이면 stack에서 '('이 나올 때까지 출력
			/* unstack tokens until left parenthesis */
			while (stack[top] != lparen)
				printToken(pop());
			pop();/* discard the left parenthesis */
		}
		else { // 연산자이거나 '('이면 
			// top에 있는 연산자의 우선 순위가 높으면 출력
			// stack의 연산자와 incoming 연산자의 우선 순위를 다르게 처리한다.
			/* remove and print symbols whose isp is greater
			than or equal to the current token’s icp */
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			// top에 있는 연산자가 incoming 연산자보다 우선순위가 낮아질 때까지 출력
			push(token);
		}
		n++;
	}
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}
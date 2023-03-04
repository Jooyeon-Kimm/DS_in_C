#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_EXPR_SIZE 100
#define MAX_STACK_SIZE 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;
char expr[MAX_EXPR_SIZE];
int stack[MAX_STACK_SIZE];
int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };
int top = 0;
precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];

	switch (*symbol)
	{
	case'(':return lparen;
	case')':return rparen;
	case'+':return plus;
	case'-':return minus;
	case'/':return divide;
	case'*':return times;
	case'%':return mod;
	case'\0':return eos;
	default:return operand;
	}
}

void push(precedence token)
{
	
	stack[++top] = token;
}

precedence pop()
{
	return stack[top--];
}

void printToken(precedence token)
{
	switch (token)
	{
	case lparen:printf("( "); break;
	case rparen:printf(") "); break;
	case plus:printf("+ "); break;
	case minus:printf("- "); break;
	case divide:printf("/ "); break;
	case times:printf("* "); break;
	case mod:printf("% "); break;
	case eos:printf("\0"); break;
	}

}

int eval(void)
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	int top = -1;
	token = getToken(&symbol, &n);
	while (token != eos)
	{
		if (token == operand)
			push(symbol - '0');
		else {
			op2 = pop(); op1 = pop();
			switch (token)
			{
			case plus:push(op1 + op2); break;
			case minus:push(op1 - op2); break;
			case times:push(op1 * op2); break;
			case divide:push(op1 / op2); break;
			case mod: push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

void postfix(void)
{
	char symbol; precedence token;
	int n = 0;
	stack[0] = eos;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
			printf("%c ", symbol);
		else if (token == rparen)
		{
			while (stack[top] != lparen)
				printToken(pop());
			pop();
		}
		else {
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}

	while ((token = pop()) != eos)printToken(token);
	printf("\n");
}

int main()
{
	char filename[10];
	scanf("%s", filename);

	FILE* fp = fopen(filename, "rt");
	if (fp == NULL){
		perror("Error opening file");
		exit(1);
	}

	fscanf(fp, "%s", &expr);
	printf("%s\n", expr);
	postfix();
	
	
	printf("%d", eval());
	return 0;
}
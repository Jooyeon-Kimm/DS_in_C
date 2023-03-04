#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
    
typedef struct {
	int key;
} element;
element* stack;

int capacity = 1;
int top = -1;

void stackFull();
int stackEmpty();
void push(element item);
element pop();

int main(void) {
	stack = malloc(sizeof(*stack));
	char inst;
    int data;
    element item;
    
	while (1) {
		scanf("%s", &inst);
		fgetc(stdin);    //버퍼 비우기
        
		switch(inst) {
            case 'I':
            scanf("%d", &data);
            fgetc(stdin);    //버퍼 비우기
                
            item.key = data;
            push(item);
            break;
                
            case 'D':
                if (stackEmpty()) { 
                	printf("Stack Empty\n");
                }
            	pop();
                break;
                
            case 'F':
                 for (int i=0; i<=top; i++) {
                     printf("%d ", stack[i].key);
                 }
                exit(1);
                break;
            
        }

	}

}


void stackFull()
{
    stack = realloc(stack, 2 * capacity * sizeof(*stack) );
	// REALLOC( stack, 2*capacity*sizeof(*stack) ); // p.58
	capacity *= 2;
}


int stackEmpty()
{
	if (top < 0) {
        return 1;
    }
    else return 0;
}


void push(element item)
{	/* add an item to the global stack */
	if ( top >= capacity-1 )
	stackFull();
	stack[++top] = item;
}


element pop()
{/* delete and return the top element from the stack */
	if (top == -1)
		stackEmpty(); /* returns an error key */
	return stack[top--];
}
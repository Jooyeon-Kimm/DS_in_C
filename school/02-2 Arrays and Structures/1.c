#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x, y) ( ((x) < (y)) ? -1 : ((x) == (y) ? 0: 1 ) )
#define MAX_TERMS 100

typedef struct {
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

polynomial* input(polynomial* p, int start, int end, char name);
void print(polynomial *p, int *start, int *end);
void attach(float coefficient, int exponent);
void padd(int starta, int enda, int startb, int endb, int* startd, int* endd);

int main(void)
{
    int numa, numb, i;
    printf("<< D(x) = A(x) + B(x) >>\n");
    printf("Input the number of items of A(x) : ");
    scanf("%d", &numa);
    printf("Input the number of items of B(x) : ");
    scanf("%d", &numb);

    int starta = 1, enda = numa;
    int startb = enda +1, endb = startb + numb -1;
    int startd, endd;
    
    printf("input in descending order\n");
    input(terms, starta, enda, 'A');
    input(terms, startb, endb, 'B');

    avail = endb + 1;
    padd(starta, enda, startb, endb, &startd, &endd);
    
    
    printf("A(x) = ");
    print(terms, &starta, &enda);
    
    printf("B(x) = ");
    print(terms, &startb, &endb);
    
    printf("D(x) = ");
    print(terms, &startd, &endd);
    
    
    
}

void attach(float coefficient, int exponent) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial.\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;

}


void padd(int starta, int enda, int startb, int endb, int* startd, int* endd) {
    /* add A(x) and B(x) to obtain D(x) */
    float coefficient;
    *startd = avail;
    
    while( starta <= enda && startb <= endb ) {
        switch( COMPARE(terms[starta].expon, terms[startb].expon)) { // 최고차항의 지수 비교
        
        case -1: // a expon < b expon
        attach(terms[startb].coef, terms[startb].expon);
        startb++;; break;

        case 0: // a expon == b expon
        coefficient = terms[starta].coef + terms[startb].coef;
        if(coefficient) attach(coefficient, terms[starta].expon);
        starta++; startb++; break;
    
        case 1: // a expon > b expon
        attach(terms[starta].coef, terms[starta].expon);
        starta++; break;

       }
       *endd = avail-1;

    }
    
    // add in remaining terms of A(x)
    for(; starta <= enda; starta++){
        attach(terms[starta].coef, terms[starta].expon); 
    }

    // add in remaining terms of B(x)
    for(; startb <= endb; startb++){
        attach(terms[startb].coef, terms[startb].expon);
    }
}


polynomial* input(polynomial* p, int start, int end, char name) {
    for(int i=start; i<=end; i++) {
        if(i==1) {
            printf("the 1st ");
        }
        else if(i==2) {
            printf("the 2nd ");
        }
        else if(i==3) {
            printf("the 3rd ");
        }
        else {
            printf("the %dth ", i);
        }

        if(i <= end) {
            printf("coefficient and exponent of %c, (ex)10 3 : ", name);
            scanf("%f %d", &p[i].coef, &p[i].expon);
        }
    
    }
    
    return p;

}

void print(polynomial *p, int* start, int* end) {
    for(int i=*start; i<=*end; i++) {
        if(p[i].expon == 0) printf("%6f\n", p[i].coef);
        else printf("%6fx^%d + ", p[i].coef, p[i].expon);
    } 
    
    if (p[*end].expon != 0) {
        printf("%6fx^%d\n", p[*end].coef, p[*end].expon);
    }
}

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

polynomial* input(polynomial *p, FILE* fp, int starta, int enda, int startb, int endb);
void print(polynomial *p, int *start, int *end);
void attatch(float coefficient, int exponent);
void padd(int starta, int enda, int startb, int endb, int* startd, int* endd);

int main(void)
{
    
    FILE* fp = fopen("in.txt", "rt");
    // 파일 열기 실패
	if (fp == NULL) {
		perror("Error opening file");
	}
    
    int a, b;
    fscanf(fp, "%d", &a);
    fscanf(fp, "%d", &b);
    
    int starta = 1, enda = a;
    int startb = enda +1, endb = startb + b -1;
    int startd, endd;
    
    input(terms, fp, 1, a, a+1, a+b);
    avail = endb + 1;
    padd(starta, enda, startb, endb, &startd, &endd);
    
    printf("A(x) = ");
    print(terms, &starta, &enda);
    
    printf("B(x) = ");
    print(terms, &startb, &endb);
    
    printf("D(x) = ");
    print(terms, &startd, &endd);
    
  
    
    
    
}

void attatch(float coefficient, int exponent) {
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
        attatch(terms[startb].coef, terms[startb].expon);
        startb++;; break;

        case 0: // a expon == b expon
        coefficient = terms[starta].coef + terms[startb].coef;
        if(coefficient) attatch(coefficient, terms[starta].expon);
        starta++; startb++; break;
    
        case 1: // a expon > b expon
        attatch(terms[starta].coef, terms[starta].expon);
        starta++; break;

       }
       *endd = avail-1;
    }
    
    // add in remaining terms of A(x)
    for(; starta <= enda; starta++){
        attatch(terms[starta].coef, terms[starta].expon); 
    }

    // add in remaining terms of B(x)
    for(; startb <= endb; startb++){
        attatch(terms[startb].coef, terms[startb].expon);
    }
}


polynomial* input(polynomial *p, FILE* fp, int starta, int enda, int startb, int endb) {
    for(int i=starta; i<=enda; i++) {
        fscanf(fp, "%f %d", &p[i].coef, &p[i].expon);
    } puts("");
    
    for(int i=startb; i<=endb; i++) {
        fscanf(fp, "%f %d", &p[i].coef, &p[i].expon);
    }
    
    

}

void print(polynomial *p, int* start, int* end) {
    for(int i=*start; i<=*end; i++) {
        if(p[i].expon == 0) printf("%6f\n", p[i].coef);
        else printf("%6fx^%d + ", p[i].coef, p[i].expon);
    } 
    
    if (p[*end].expon != 0) {
        printf("%6fx^%d/n", p[*end].coef, p[*end].expon);
    }
}
​
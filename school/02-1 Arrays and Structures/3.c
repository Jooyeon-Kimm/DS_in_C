#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct {
	char name[10];
	int age;
	float salary;
} humanBeing;

int humansEqual(humanBeing* person1, humanBeing* person2)
{
	if (strcmp(person1->name, person2->name))
		return FALSE;
	if (person1->age != person2->age)
		return FALSE;
	if (person1->salary != person2->salary)
		return FALSE;
	return TRUE;
}

int main(void) {

	humanBeing person1, person2;

	/* gets로 공백 받기
	gets(person1.name)
	scanf("%f*c", &person1.salary)
	*/

	// person1 입력
	printf("Input person1's name, age, salary : ");
	gets(person1.name);
	scanf("%d %f",&person1.age, &person1.salary);
	getchar();

	// person2 입력
	printf("Input person2's name, age, salary : ");
	gets(person2.name);
	scanf("%d %f",&person2.age, &person2.salary);

	printf("person1: name: %s age: %d salary: %f\n", person1.name, person1.age, person1.salary);
	printf("person2: name: %s age: %d salary: %f\n", person2.name, person2.age, person2.salary);

	printf("The two human beings are ");
	if (humansEqual(&person1, &person2) == 1) {
		printf("same.\n");
	}
	else {
		printf("not the same.\n");
	}

}
​
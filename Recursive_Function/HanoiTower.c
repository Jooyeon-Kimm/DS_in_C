#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
Hanoi Tower

Ex)
Move all the disks from Tower1 to Tower 3
size: C > B > A

   A        -       -
   B        -       -
   C        -       -
Tower 1, Tower 2, Tower 3
*/


// Hanoi Tower Function
// Move 3 disks from stick_from to stick_to via stick_via
int HanoiTower(int N, char from, char via, char to)
{
	if (N == 1)	// if there's only one disk
	{
		printf("Move disk 1 from Stick %c to Stick %c\n", from, to);
	}

	else // two or more disks
	{
		HanoiTower(N - 1, from, to, via);
		printf("Move disk %d from Stick %c to Stick %c\n", N, from, to);
		HanoiTower(N - 1, via, from, to);

	}


}
int main(void)
{
	int height = 3;	// Number of Disks
	int width = 3;	// Number of sticks
	int N = height;	// Number of Disks

	// Move 3 disks from stick A to stick C via stick B
	// 원반 3개를 막대 A에서 C로 옮기기 (막대 B를 경유하여)

	HanoiTower(N, 'A', 'B', 'C');
	
}
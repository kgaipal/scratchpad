#include <stdio.h>

void func(int* arg1)
{
	printf("%d =>", arg1);
	printf("%d\n", *arg1);
}

int main ()
{
	int avar = 9;
	int *p = malloc(1);
	func(1);
	return 0;
}

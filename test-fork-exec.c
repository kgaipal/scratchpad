#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("[%d] hello world\n", getpid());
	int rv = fork();

	if (rv > 0) {
		wait(NULL);
		printf("[%d] *parent*\n", getpid());
	} else if (rv == 0) {
		sleep(2);
		printf("[%d] *child*\n", getpid());
	} else {
		printf("[%d] *????*\n", getpid());
	}
}

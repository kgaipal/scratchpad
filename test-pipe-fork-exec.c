/* compile gcc test-pipe-fork-exec.c */
/* taken from  http://stackoverflow.com/questions/23419128/learning-pipes-exec-fork-and-trying-to-chain-three-processes-together?rq=1 */

int main(int argc, char *argv[])
{
	int pfd[2];                                     /* Pipe file descriptors */
	int pfd2[2];

	if (pipe(pfd) == -1)                            /* Create pipe */
		perror("pipe");

	if (pipe(pfd2) == -1)                            /* Create pipe */
		perror("pipe");

	/*
	  Fork process 1 and exec ls command
	  write to pfd[1], close pfd[0]
	*/
	switch (fork()) {
	case -1:
		perror("fork");
	case 0:
		if (close(pfd[0]) == -1)
			perror("close 1");

		// dup stdout on pfd[1]
		if (pfd[1] != STDOUT_FILENO) {
			if (dup2(pfd[1], STDOUT_FILENO) == -1)
				perror("dup2 2");
			if (close(pfd[1]) == -1)
				perror("close 4");
		}
		execlp("ls", "ls", (char *) NULL);
		perror("execlp ls");
	default:
		break;
	}

	/*
	 * Fork process 2 and exec wc command
	 read from pfd[0], close pfd[1]
	 write to pfd[1], close pfd2[0]
	*/
	switch (fork()) {
	case -1:
		perror("fork");
	case 0:
		// read from pfd[0]
		if (close(pfd[1]) == -1)
			perror("close 3");

		if (pfd[0] != STDIN_FILENO) {
			if (dup2(pfd[0], STDIN_FILENO) == -1)
				perror("dup2 2");
			if (close(pfd[0]) == -1)
				perror("close 4");
		}

		if (pfd2[1] != STDOUT_FILENO) {
			if (dup2(pfd2[1], STDOUT_FILENO) == -1)
				perror("dup2 2");
			if (close(pfd2[1]) == -1)
				perror("close 4");
		}

		execlp("cat", "cat", (char *) NULL);
		perror("execlp cat");
	default:
		break;
	}

	/*
	 *   Fork process 3
	 */
	switch (fork()) {
	case -1:
		perror("fork");
	case 0:
		if (close(pfd2[1]) == -1)
			perror("close 3");

		if (pfd2[0] != STDIN_FILENO) {
			if (dup2(pfd2[0], STDIN_FILENO) == -1)
				perror("dup2 2");
			if (close(pfd2[0]) == -1)
				perror("close 4");
		}

		execlp("wc", "wc", "-l", (char *) NULL);
		perror("execlp wc");
	default:
		break;
	}


	/* Parent closes unused file descriptors for pipe, and waits for children */

	if (close(pfd[0]) == -1)
		perror("close 5");
	if (close(pfd[1]) == -1)
		perror("close 6");
	if (close(pfd2[0]) == -1)
		perror("close 5");
	if (close(pfd2[1]) == -1)
		perror("close 6");

	if (wait(NULL) == -1)
		perror("wait 1");
	if (wait(NULL) == -1)
		perror("wait 2");
	if (wait(NULL) == -1)
		perror("wait 3");

	exit(EXIT_SUCCESS);
}

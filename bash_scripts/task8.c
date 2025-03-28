#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SIZE 100

int main() {
	int fd[2];
	if (pipe(fd) == -1) {
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	char msg[SIZE] = {0};
	pid_t pid = fork();
	if (pid == -1) {
		perror("Fork");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		printf("Child process started execution...\nEnter the text you wanna send to parent:\n");
		fgets(msg, SIZE, stdin);
		close(fd[0]);
		if (write(fd[1], msg, sizeof(msg)) != sizeof(msg)) {
			perror("Write");
			close(fd[1]);
			exit(EXIT_FAILURE);
		}
		printf("Child process exits...\n");
		close(fd[1]);
		exit(EXIT_SUCCESS);
	} else {
		close(fd[1]);
		int status;
		wait(&status);
		int exit_status = WEXITSTATUS(status);
		if (exit_status == EXIT_SUCCESS) {
			if (read(fd[0], msg, SIZE) < 1) {
				perror("Read");
				close(fd[0]);
				exit(EXIT_FAILURE);
			}
		} else {
			printf("Child didn't send anything\n");
			close(fd[0]);
			return (-1);
		}
		close(fd[0]);
		printf("Message recieved from child: %s", msg);
		return (0);
	}
}
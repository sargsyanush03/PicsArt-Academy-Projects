#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

unsigned long long factorial(int n);
void clean_up(int fd1, int fd2, char* err_msg);

int main() {
	int pipe1[2];
	int pipe2[2];
	if (pipe(pipe1) == -1) {
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe2) == -1) {
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid == -1) {
		perror("Fork");
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		printf("Child process started execution...\n");
		close(pipe1[1]);
		close(pipe2[0]);
		int num = 0;
		int ret_val = read(pipe1[0], &num, sizeof(num));
		if (ret_val != sizeof(num)) {
			clean_up(pipe1[0],pipe2[1], "Error reading number from parent");
		}
		unsigned long result = factorial(num);
		ret_val = write(pipe2[1], &result, sizeof(result));
		if (ret_val != sizeof(result)) {
			clean_up(pipe1[0],pipe2[1], "Error writing result to  parent's pipe");
		}
		printf("The result in child process is %lu.\nChild process exits...\n", result);
		exit(EXIT_SUCCESS);
	} else {
		close(pipe1[0]);
		close(pipe2[1]);
		int num = 0;
		printf("Please enter a number: ");
		scanf("%d", &num);
		if (num < 0) {
			kill(pid, SIGKILL);
			clean_up(pipe1[1], pipe2[0], "Enter a positive number");

		}
		int ret_val = write(pipe1[1], &num, sizeof(num));
		if (ret_val != sizeof(num)) {
			kill(pid, SIGKILL);
			clean_up(pipe1[1], pipe2[0], "Error writing number to child's pipe");
		}
		unsigned long result;
		int status;
		wait(&status);
		int exit_status = WEXITSTATUS(status);
		if (exit_status == EXIT_SUCCESS) {
			ret_val = read(pipe2[0], &result, sizeof(result));
			if (ret_val != sizeof(result)) {
				kill(pid, SIGKILL);
				clean_up(pipe1[1], pipe2[0], "Read error");
			}
		} else {
			clean_up(pipe1[1], pipe2[0], "Child didn't send anything");
		}
		printf("Result recieved from child - %lu\n", result);
		close(pipe1[1]);
		close(pipe2[0]);
		exit(EXIT_SUCCESS);
	}
}
void clean_up(int fd1, int fd2, char* err_msg) {
	perror(err_msg);
	close(fd1);
	close(fd1);
	exit(EXIT_FAILURE);
}

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
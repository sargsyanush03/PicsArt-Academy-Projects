#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void clean_up(int server_fd, int client_fd, char* err_msg) {
	perror(err_msg);
	if (server_fd > 2) {
		close(server_fd);
	}
	if (client_fd > 2) {
		close(client_fd);
	}
	exit(EXIT_FAILURE);
}
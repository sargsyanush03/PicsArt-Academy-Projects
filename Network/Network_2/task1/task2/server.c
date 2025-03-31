#include <stdio.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE 256
#define PORT 8080
#define MAX_CLIENTS 10
int server_setup();
void recv_send_data(fd_set* tmp, fd_set* read_set, int max_fd);

int main() {
	int server_fd = server_setup();
	if (server_fd == -1) {
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	fd_set read_set, tmp;
	FD_ZERO(&read_set);
	FD_SET(server_fd, &read_set);
	int max_fd = server_fd;

	while (1) {
		tmp = read_set;
		select(max_fd + 1, &tmp, NULL, NULL, NULL);
//accept new client connections and add them to the set
		if (FD_ISSET(server_fd, &tmp)) {
			int client = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
			if (client == -1) {
				perror("Accept");
				continue;
			}
			FD_SET(client, &read_set);
			max_fd = client > max_fd ? client : max_fd;
		}
		recv_send_data(&tmp, &read_set, max_fd);
	}
}

void recv_send_data(fd_set* tmp, fd_set* read_set, int max_fd) {
	char msg[SIZE] = {0};
	int msg_len = 0;
	for (int i = 4; i <= max_fd; ++i) {
		if (FD_ISSET(i, tmp)) {
			msg_len = recv(i, msg, SIZE, 0);
			if (msg_len <= 0) {
				printf("Client disconnected...\n");
				FD_CLR(i, read_set);
				close(i);
				max_fd = max_fd == i ? max_fd - 1 : max_fd;
			} else {
				msg[msg_len] = 0;
				printf("ID:%d %s\n\n", i, msg);
				msg_len = send(i, msg, msg_len, 0);
				if (msg_len <= 0) {
					printf("Client disconnected...\n");
					close(i);
					FD_CLR(i, read_set);
					max_fd = max_fd == i ? max_fd - 1 : max_fd;
				}
			}
		}
	}
}

int server_setup() {
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		perror("Socket() error");
		return (-1);
	}
	if (bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
		perror("Bind() error");
		return (-1);
	}
	if (listen(fd, MAX_CLIENTS) != 0) {
		perror("Listen() error");
		return(-1);
	}
	return(fd);
}
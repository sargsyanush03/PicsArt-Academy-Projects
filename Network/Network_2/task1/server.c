#include <stdio.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SIZE 256
#define PORT 8080
#define MAX_CLIENTS 10
#define PATH "chat.txt"

int setup_server();
void recv_data(fd_set* tmp,fd_set* read_fds,int max_fd,char* msg);

int main() {
//open new file for saving messages
	unlink(PATH);
	FILE* stream = fopen(PATH, "w+");
	if (!stream) {
		perror("Fopen() error");
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	int server_fd, max_fd;
	server_fd = setup_server();
	if (server_fd == -1) {
		perror("Server setup is failed");
		exit(EXIT_FAILURE);
	}
	char msg[SIZE];
	max_fd = server_fd;
	fd_set read_fds, tmp;
	FD_ZERO(&read_fds);
	FD_SET(server_fd, &read_fds);
	while (1) {
		memset(msg, 0, SIZE);
		tmp = read_fds;
		select(max_fd + 1, &tmp, NULL, NULL, NULL);
		if (FD_ISSET(server_fd, &tmp)) {
//add new client connection to the set
			int client = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
			if (client == -1) {
				perror("Accept() error");
				continue;
			}
			FD_SET(client, &read_fds);
			max_fd = max_fd > client ? max_fd : client;
		}
//recieve data from client and send to others
		recv_data(&tmp, &read_fds, max_fd, msg);
//save the message in file
		fprintf(stream, "%s\n", msg);
		fflush(stream);
	}
	
}

int setup_server() {
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		perror("Socket() error");
		return (-1);
	}
	struct sockaddr_in server_addr;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("Bind() error");
		return(-1);
	}
	if (listen(server_fd, MAX_CLIENTS) == -1) {
		perror("Listen() error");
		return (-1);
	}
	printf("Server is running on port %d\n", PORT);
	return (server_fd);
}

void recv_data(fd_set* tmp,fd_set* read_fds,int max_fd,char* msg) {
	int msg_len = 0;
	int sender = 0;
	for (int i = 5; i <= max_fd; ++i) {
		if (FD_ISSET(i, tmp)) {
			sender = i;
			msg_len = recv(i, msg, SIZE, 0);
			if (msg_len <= 0) {
				printf("Client disconnected...\n");
				FD_CLR(i, read_fds);
				close(i);
				max_fd = max_fd == i ? max_fd - 1 : max_fd;
			} else {
				msg[msg_len] = 0;
				printf("%s\n", msg);
				for (int i = 5; i <= max_fd; ++i) {
					if (i != sender) {
						msg_len = send(i, msg, msg_len, 0);
						if (msg_len <= 0) {
							printf("Client disconnected\n");
							FD_CLR(i, read_fds);
							close(i);
							max_fd = max_fd == i ? max_fd - 1 : max_fd;
						}
					}
				}
			}
		}
	}
}
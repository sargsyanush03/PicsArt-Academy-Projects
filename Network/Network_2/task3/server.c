#include <stdio.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>

#define SIZE 256
#define PORT 8080
#define MAX_CLIENTS 10
#define FILENAME_SIZE 50

int setup_server();
void read_send_data(int* fd);

int main() {
//setup the server
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	int server_fd = setup_server();
	if (server_fd == -1) {
		perror("Server setup is failed");
		exit(EXIT_FAILURE);
	}
	int new_socket, i = 1;
	struct pollfd fds[MAX_CLIENTS + 1];
	fds[0].fd = server_fd;
	fds[0].events = POLLIN;
	fds[0].revents = 0;
	for (i = 1; i <= MAX_CLIENTS; ++i) {
		fds[i].fd = -1;
		fds[i].events = POLLIN;
	}
	while (1) {
		poll(fds, MAX_CLIENTS + 1, -1);
//see if there's a connection request
		if (fds[0].revents & POLLIN) {
//accept request
			new_socket = accept(fds[0].fd, (struct sockaddr*)&client_addr, &addr_len);
			if (new_socket == -1) {
				perror("Accept() error");
				continue;
			}
			printf("ID:%d new connection\n", new_socket);
//add to available place in array
			for (i = 1; i <= MAX_CLIENTS; ++i) {
				if (fds[i].fd == -1) {
					fds[i].fd = new_socket;
					break;
				}
			}
//check if client sended anything after connecting
			poll(fds, MAX_CLIENTS + 1, 0);
//if array if full, don't add anything
			if (i > MAX_CLIENTS) {
				printf("Too many clients!\n");
				close(new_socket);
			}
//recieve data from available clients
			for (i = 1; i <= MAX_CLIENTS; ++i) {
				if (fds[i].fd != -1 && (fds[i].revents & POLLIN)) {
					read_send_data(&(fds[i].fd));
				}
			}

		}
	}
}

void read_send_data(int* fd) {
//read filename from client
	char filename[FILENAME_SIZE];
	char line[SIZE];
	int len = recv(*fd, filename, FILENAME_SIZE, 0);
	if (len <= 0) {
		printf("ID:%d disconnected...\n" ,*fd);
		close(*fd);
		*fd = -1;
	}
	len = strlen(filename);
	filename[len] = 0;
	printf("Filename: <%s>\n",filename);
//open corresponding file
	FILE* stream = fopen(filename, "r");
	if (!stream) {
		printf("No such file or directory\n");
		close(*fd);
		*fd = -1;
		return;
	}
	char* ret_val = NULL;
//send each line to client
	while (1) {
		ret_val = fgets(line, SIZE, stream);
		if (ret_val == NULL) {
			close(*fd);
			*fd = -1;
			break;
		}
		len = strlen(line);
		len = send(*fd, line, len , 0);
		if (len <= 0) {
			printf("ID:%d disconnected...\n" ,*fd);
			close(*fd);
			*fd = -1;
		}
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


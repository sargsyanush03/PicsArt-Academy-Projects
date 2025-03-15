#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>

#define PORT 8080
#define SIZE 300


int main() {

	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
//create a socket and listen to connections
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
		perror("Bind error");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 5) != 0) {
		perror("Listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
	if (client_fd == -1) {
		perror("Accept failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	char msg[SIZE] = {0};
	if (read(client_fd, msg, SIZE) < 1) {
		perror("Error reading message from socket");
		close(server_fd);
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	printf("Message recieved from client\n");
	printf("\"%s\"\n",msg);
	strcpy(msg + strlen(msg), "\"\n\"Text from server\"");
	if (write(client_fd, msg, SIZE) < 1) {
		perror("Error writing message into socket");
		close(server_fd);
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	close(client_fd);
	close(server_fd);
	return (0);
}
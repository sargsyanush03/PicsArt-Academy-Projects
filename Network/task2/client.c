#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#define SERVER_IP  "127.0.0.1"
#define PORT 8080
#define SIZE 300

int main(int argc, char** argv) {

//create socket and connect to the server
	int sock_fd;
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) != 1) {
		perror("Error: Invalid IP address format");
		exit(EXIT_FAILURE);
	}
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	if (connect(sock_fd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
		perror("Error connecting to server");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	printf("Enter the message you want to send to the server.\n");
//send the message to the server
	char msg[SIZE] = {0};
	fgets(msg, SIZE, stdin);
	msg[strlen(msg) - 1] = 0;
	if (write(sock_fd, msg, strlen(msg)) != strlen(msg)) {
		perror("Error sending message over socket");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	memset(msg, 0, SIZE);
	if (read(sock_fd, msg, SIZE) < 1) {
		perror("Error reading message from socket");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	msg[strlen(msg) - 1] = 0;
	printf("Message recieved from server\n");
	printf("\"%s\"", msg);
	close(sock_fd);
	return(0);
}

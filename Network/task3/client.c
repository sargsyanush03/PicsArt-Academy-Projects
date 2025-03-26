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
#define SIZE 100
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
//recieve time from server
	char info[SIZE] = {0};
	if (read(sock_fd, info, SIZE) < 1) {
		perror("Reading from socket failed");
		close(sock_fd);
		exit(EXIT_FAILURE);	
	}
	printf("%s\n", info);
	close(sock_fd);
	return (0);	
}
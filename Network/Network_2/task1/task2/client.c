#include <stdio.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define SIZE 256

int connect_to_server();

int main(int argc, char** argv) {
	int sock_fd = connect_to_server();
	if (sock_fd == -1) {
		exit(EXIT_FAILURE);
	}
	char str[SIZE];
	char* ret_val;
	int byte_count = 0;
	while (1) {
		ret_val = fgets(str, SIZE, stdin);
		if (ret_val == NULL) {
			break;
		}
		byte_count = strlen(str);
		str[byte_count - 1] = 0;
		--byte_count;
		byte_count = send(sock_fd, str, byte_count, 0);
		if (byte_count <= 0) {
			printf("Server disconnection\n");
			close (sock_fd);
			exit(EXIT_FAILURE);
		} 
		byte_count = recv(sock_fd, str, SIZE, 0);
		if (byte_count <= 0) {
			printf("Server disconnection\n");
			close(sock_fd);
			exit(EXIT_FAILURE);
		}
		str[byte_count] = 0;
		printf("%s\n", str);
	}
}


int connect_to_server() {
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) == 0) {
		perror("Inet_pton() error");
		return (-1);
	}
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		perror("Socket() error");
		return (-1);
	}
	if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("Connect() error");
		close(sock_fd);
		return (-1);
	}
	return (sock_fd);
}
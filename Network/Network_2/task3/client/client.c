#include <stdio.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define SIZE 256

int connect_to_server();

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("USAGE: <%s> <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int sock_fd = connect_to_server();
	if (sock_fd == -1) {
		exit(EXIT_FAILURE);
	}
	int len = send(sock_fd, argv[1],strlen(argv[1]), 0);
	if (len <= 0)  {
		perror("Server disconnection...\n");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	FILE* stream = fopen(argv[1], "w");
	if (!stream) {
		perror("Fopen() error");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	char* ret_val = NULL;
	char line[SIZE];
	len = 0;
	int i = 0;
	while (1) {
		len = recv(sock_fd, line, SIZE, 0);
		i++;
		if (len <= 0) {
			if (i == 1) {
				printf("No such file or directory\n");
				unlink(argv[1]);
			} else {
				printf("File content is sended\nUse <cat %s> to see result.\n",argv[1]);
			}
			printf("Server disconnection...\n");
			fflush(stream);
			fclose(stream);
			close(sock_fd);
			break;
		}
		line[len] = 0;
		fprintf(stream, "%s", line);
	}

}

int connect_to_server() {
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
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
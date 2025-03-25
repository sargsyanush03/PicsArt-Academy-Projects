#include "expression.h"

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
		clean_up(-1, sock_fd, "Error connecting to server");//-1 means no argument
	} 
	printf("Enter the expression.\nExpression format: <number> <opcode> <number>\n");
	char exp[SIZE] = {0};
	fgets(exp, SIZE, stdin);
	size_t len = strlen(exp);
	exp[len - 1] = 0;
	if (write(sock_fd, exp, len) != len) {
		clean_up(-1, sock_fd, "Error sending expression over socket");
	}
//read the result of expression
	memset(exp, 0, len);
	if (read(sock_fd, exp, SIZE) < 1) {
		clean_up(-1, sock_fd, "Error reading result from socket");
	}
	printf("%s\n",exp);
	close(sock_fd);
	return (0);
}
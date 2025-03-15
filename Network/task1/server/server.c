#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>

#define PORT 8080
#define SIZE 30

int main() {

	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
//create a socket and listen to connections
	printf("Server's PORT - %d\n", PORT);
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
//read the filename and file size 
	int size = 0;
	char filename[SIZE] = {0};
	if (read(client_fd, filename, SIZE) < 1) {
		perror("Can't read the filename");
		close(server_fd);
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	if (recv(client_fd, &size, sizeof(size), 0) < 1) {
		perror("Can't read the file size");
		close(server_fd);
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	size = ntohl(size);//convert to machine's byte order
//open a file with the same name and write the content
	int new_file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (new_file == -1) {
		perror("Open failed");
		close(server_fd);
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	char* buffer = (char*)malloc(sizeof(char) * size);
	if (!buffer) {
		perror("Error allocating memory");
		close(server_fd);
		close(client_fd);
		close(new_file);
		free(buffer);
		exit(EXIT_FAILURE);
	}
	if (read(client_fd, buffer, size) != size) {
		perror("Error reading file");
		close(server_fd);
		close(client_fd);
		close(new_file);
		free(buffer);
		exit(EXIT_FAILURE);
	}
	if (write (new_file, buffer, size) != size) {
		perror("Error writing file");
		close(server_fd);
		close(new_file);
		close(client_fd);
		free(buffer);
		exit(EXIT_FAILURE);
	}
	close (server_fd);
	close(client_fd);
	close(new_file);
	free(buffer);
}

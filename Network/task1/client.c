#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

	if (argc != 4) {
		printf("USAGE: <%s> <IP address> <Port number> <Filename>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
//open the file and read file content into buffer
	int fd = open(argv[3], O_RDONLY);
	if (fd == -1) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	} 
	struct stat obj;
	fstat(fd, &obj);
	char* buffer = (char*)malloc(sizeof(char) * obj.st_size);
	if (!buffer) {
		perror("Error allocating memory");
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (read(fd, buffer, obj.st_size) != obj.st_size) {
		perror("Error reading file");
		close(fd);
		free(buffer);
		exit(EXIT_FAILURE);
	}
	close(fd);
//create socket and connect to the server
	int sock_fd;
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) != 1) {
		perror("Error: Invalid IP address format");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		perror("Error creating socket");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	if (connect(sock_fd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
		perror("Error connecting to server");
		close(sock_fd);
		free(buffer);
		exit(EXIT_FAILURE);
	}
//send the filename to the server
	if (write(sock_fd, argv[3], strlen(argv[3])) != strlen(argv[3])) {
		perror("Error sending filename over socket");
		close(sock_fd);
		free(buffer);
		exit(EXIT_FAILURE);
	}
	int size = htonl(obj.st_size); //convert to network byte order
//send the file size to the server
	if (write(sock_fd, &size, sizeof(size)) != sizeof(size)) {
		perror("Error sending file size over socket");
		close(sock_fd);
		free(buffer);
		exit(EXIT_FAILURE);
	}

//send file's content to the server
	if (write(sock_fd, buffer, obj.st_size) != obj.st_size) {
		perror("Error sending file's content over socket");
		close(sock_fd);
		free(buffer);
		exit(EXIT_FAILURE);
	}
	printf("File content is sended\n");
	close(sock_fd);
	free(buffer);
	return(0);
}

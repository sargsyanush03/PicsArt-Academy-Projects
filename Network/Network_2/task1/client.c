#include <stdio.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define SIZE 256
#define PATH "chat.txt"

int connect_to_server();
void show_previous_msgs();
void complete_msg(char* complete_msg,char* name);

int main(int argc, char** argv) {
//enter username
	if (argc != 2) {
		printf("USAGE: <%s> <your_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int sock_fd = connect_to_server();
	if (sock_fd == -1) {
		exit(EXIT_FAILURE);
	}
	show_previous_msgs();
	char msg[SIZE];
	fd_set read_fds, tmp;
	FD_ZERO(&read_fds);
	FD_SET(STDIN_FILENO, &read_fds);
	FD_SET(sock_fd, &read_fds);
	int max_fd = sock_fd;
	int msg_len = 0;
	while (1) {
		tmp = read_fds;
		memset(msg, 0, SIZE);
		select(max_fd + 1, &tmp, NULL, NULL, NULL);
		if (FD_ISSET(sock_fd, &tmp)) {
			msg_len = recv(sock_fd, msg, SIZE, 0);
			if (msg_len <= 0) {
				perror("Server disconnected\n");
				close(sock_fd);
				exit(EXIT_FAILURE);
			} else {
				printf("%s\n",msg);
			}
		} 
		else if (FD_ISSET(STDIN_FILENO, &tmp)) {
//add to msg "username: <msg>" format
			complete_msg(msg, argv[1]);
			msg_len = strlen(msg);
			int ret_val = send(sock_fd,msg, msg_len, 0);
			if (ret_val <= 0) {
				perror("Server disconnected\n");
				close(sock_fd);
				exit(EXIT_FAILURE);
			}
		}
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

void show_previous_msgs() {
	FILE* stream = fopen(PATH, "r");
	if (!stream) {
		perror("Fopen() error");
		exit(EXIT_FAILURE);
	} 
	char msg[SIZE];
	char* ret_val;
	while (1) {
		memset(msg, 0, SIZE);
		ret_val = fgets(msg, SIZE, stream);
		if (ret_val == NULL)
			break;
		printf("%s",msg);
	}
	fclose(stream);
}

void complete_msg(char* complete_msg,char* name) {
	strcat(complete_msg, name);
	strcat(complete_msg, ": ");
	char msg[100];
	fgets(msg, SIZE, stdin);
	int len = strlen(msg);
	msg[len - 1] = 0;
	strcat(complete_msg, msg);
	len = strlen(complete_msg);
}
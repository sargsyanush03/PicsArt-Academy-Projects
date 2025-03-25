#include "expression.h"

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
		clean_up(server_fd, -1, "Bind error");
	}
	if (listen(server_fd, 1) != 0) {
		clean_up(server_fd, -1, "Error listening for connections");
	}
	client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
	if (client_fd == -1) {
		clean_up(server_fd, -1, "Accept failed");
	}
	char exp[SIZE] = {0};
	if (read(client_fd, exp, SIZE) < 1) {
		clean_up(server_fd, client_fd, "Error reading expression from socket");
	}
	printf("The expression recieved from client:\n%s\n",exp);
	Exp_details obj = {LONG_MIN, LONG_MIN, 0};
	parse_expression(exp, &obj);
	if (obj.num1 == LONG_MIN || obj.num2 == LONG_MIN || obj.opcode == 0) {
		clean_up(server_fd, client_fd, "Invalid arguments");
	}
	printf("Expresstion details:\nnumber - %ld\nopcode - %c\nnumber - %ld\n", obj.num1, obj.opcode, obj.num2);
	long result = calculate_result(&obj);
	if (result == LONG_MIN) {
		if (write(client_fd, DIV_BY_ZERO, sizeof(DIV_BY_ZERO)) != sizeof(DIV_BY_ZERO)) {
			clean_up(server_fd, client_fd, "Error writing result to socket");
		}
		close(client_fd);
		close(server_fd);
	} else if (result == LONG_MAX) {
		if (write(client_fd, INVAL_OPCODE, sizeof(INVAL_OPCODE)) != sizeof(INVAL_OPCODE)) {
			clean_up(server_fd, client_fd, "Error writing result to socket");
		}
		close(client_fd);
		close(server_fd);
	}
	printf("The result of expression - %ld\n",result);
	char* str = itoa(result);
	printf("The result as a string - %s\n",str);
	size_t len = strlen(str);
	if (write(client_fd, str, len) != len) {
		free(str);
		clean_up(server_fd, client_fd, "Error writing result to socket");
	}
	free(str);
	close(client_fd);
	close(server_fd);
}

long calculate_result(Exp_details* obj) {
	switch (obj->opcode) {
		case '+':
			return(obj->num1 + obj->num2);
		case '-':
			return(obj->num1 - obj->num2);
		case '*':
			return(obj->num1 * obj->num2);	
		case '/':
			if (obj->num2 == 0) {
				return (LONG_MIN);
			}
			return (obj->num1 / obj->num2);
		case '%':
			if (obj->num2 == 0) {
				return (LONG_MIN);
			}
			return (obj->num1 % obj->num2);
		default:
			return (LONG_MAX);
	}

}

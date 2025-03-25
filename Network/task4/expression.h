#ifndef EXP_H   
#define EXP_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

#define DIV_BY_ZERO "The division by zero is not allowed."
#define INVAL_OPCODE "Invalid opcode"
#define SERVER_IP  "127.0.0.1"
#define PORT 8080
#define SIZE 100

//struct for expression details(opcode and operands)
typedef struct {
	long num1;
	long num2;
	char opcode;
} Exp_details;

//cleanup function that prints an error message end closes fds
void clean_up(int server_fd, int client_fd, char* err_msg);
//expression parser
void parse_expression(char* expression, Exp_details* obj);
char* itoa(int num);
long calculate_result(Exp_details* obj);

#endif
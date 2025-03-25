#include "expression.h"

void parse_expression(char* exp, Exp_details* obj) {
	int i = 0;
	int result = 0;
	int sign = 1;
	//get the first operand
	while (exp[i] && (exp[i] < '0' || exp[i] > '9') && exp[i] != '-') {
		++i;
	}
	if (exp[i] == '-') {
		sign = -1;
		++i;
	}
	while (exp[i] && exp[i] >= '0' && exp[i] <= '9') {
		result = result * 10 + exp[i] - '0';
		++i;
	}
	obj->num1 = sign * result;
	sign = 1;
	result = 0;
	//get the opcode
	while (exp[i] && exp[i] != '+' && exp[i] != '-' && exp[i] != '/' && exp[i] != '*' && exp[i] != '%') {
		++i;
	}
	if (exp[i]) {
		obj->opcode = exp[i];
		++i;
	}
	//get the second operand
	while (exp[i] && (exp[i] < '0' || exp[i] > '9') && exp[i] != '-') {
		++i;
	}
	if (exp[i] == '-') {
		sign = -1;
		++i;
	}
	while (exp[i] && exp[i] >= '0' && exp[i] <= '9') {
		result = result * 10 + exp[i] - '0';
		++i;
	}
	obj->num2 = sign * result;
}
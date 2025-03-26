#include <stdlib.h>
#include <stdio.h>

int digit_count(int num) {
	int i = 0;
	while (num) {
		++i;
		num /= 10;
	}
	return (i);
}

char* itoa(int num) {
	int len = digit_count(num);
	int flag = 0;
	//if expression result is 0,return string with '0'
	if (len == 0) {
		char* result = (char*)calloc(2, sizeof(char));
		result[0] = '0';
		return (result);
	}
	
	if (num < 0) {
		len++; //place for '-'
		flag = 1;
		num *= -1;
	}
	char* result = (char*)calloc(len + 1, sizeof(char));
	if (!result) {
		perror("Memory allocation error");
		return (NULL);
	}
	if (flag) {
		result[0] = '-';
	}
	int i = len - 1;
	while (num) {
		result[i--] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}
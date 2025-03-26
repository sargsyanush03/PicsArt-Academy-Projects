#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define PORT 8080
#define SECONDS_IN_MIN 60
#define SECONDS_IN_HOUR (60 * SECONDS_IN_MIN)
#define SECONDS_IN_DAY (24 * SECONDS_IN_HOUR)
int is_leap_year(int year);
char* itoa(int num);
int write_data(int client_fd, int data);

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
	time_t raw_time;
	time(&raw_time);
	int year = 1970;
//Count years since 1970
	while (1) {
		int days_in_year = 365 + is_leap_year(year);
		if (raw_time < days_in_year * SECONDS_IN_DAY)
			break;
		raw_time -= days_in_year * SECONDS_IN_DAY;
		year++;
	}
	printf("%d/", year);
//count months
	int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i = 0;
	while (1) {
		if (i == 1 && is_leap_year(year))
			months[i] += 1;
		if (raw_time < months[i] * SECONDS_IN_DAY)
			break;
		raw_time -= months[i] * SECONDS_IN_DAY;
		++i;
	}
	printf("%d/",i + 1);
//count days
	int day = raw_time / SECONDS_IN_DAY + 1;
	printf("%d\n",day);
	raw_time %= SECONDS_IN_DAY;
//count hours
	int hours = raw_time / SECONDS_IN_HOUR;
	printf("%d:",hours + 4);
	raw_time %= SECONDS_IN_HOUR;
//count minutes
	int minutes = raw_time / SECONDS_IN_MIN;
	printf("%d\n",minutes);
	if (write_data(client_fd, year) == 0) {
		close(server_fd);
		return (1);
	}
	write(client_fd,"/", 1);
	if (write_data(client_fd, i + 1) == 0) {
		close(server_fd);
		return (1);
	}
	write(client_fd,"/", 1);
	if (write_data(client_fd, day) == 0) {
		close(server_fd);
		return (1);
	}
	write(client_fd," ", 1);
	if (write_data(client_fd, hours + 4) == 0) {
		close(server_fd);
		return (1);
	}
	write(client_fd,":", 1);	
	if (write_data(client_fd, minutes) == 0) {
		close(server_fd);
		return (1);
	}
	close(server_fd);
	return(0);
}

int write_data(int client_fd, int data) {
	char* str = itoa(data);
	size_t len = strlen(str);
	if (write(client_fd, str, len) != len) {
		perror("Writing into socket failed");
		close(client_fd);
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

int is_leap_year(int year) {
	if (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0))
		return (1);
	return(0);
}
#include <iostream>
//Circle
double area(double radius) {
	if (radius < 1) {
		return (-1);
	}
	double pi = 3.14;
	return (pi * radius * radius);
}

//Rectangle
double area(double width, double height, char type) {
	if (width < 1 || height < 1) {
		return (-1);
	}
	return (width * height);
}

//triangle
double area(double base, double height) {
	if (base < 1 || height < 1) {
		return (-1);
	}
	return (base * height / 2);
}

//Square
double area(int side) {
	if (side < 1) {
		return (-1);
	}
	return (side * side);
}


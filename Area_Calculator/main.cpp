#include <iostream>
double area(double radius);
double area(double width, double height, char type);
double area(double base, double height);
double area(int side);

void print_options() {
	std::cout
	<< "Select a shape:\n"
	<< "1. Circle\n"
    << "2. Rectangle\n"
	<< "3. Triangle\n"
	<< "4. Square\n"
	<< "5. Exit\n";
}

int main() {
	int shape = 0;
	double arg1 = 0, arg2 = 0;
	int arg3 = 0;
	int ret_val = 0;	
	while (1) {
		print_options();
		std::cin >> shape;
		if (shape == 5)
			break;
		switch (shape) {
			case 1:
				std::cout << "Enter the radius: ";
				std::cin >> arg1;
				ret_val =  area(arg1);
				if (ret_val != -1) 
					std::cout << "Area of Circle: " << ret_val << std::endl;
				else 
					std::cerr << "Invalid argument" << std::endl;
				break;
			case 2:
				std::cout << "Enter width: ";
				std::cin >> arg1;
				std::cout << "Enter height: ";
				std::cin >> arg2;
				ret_val =  area(arg1, arg2, 0); 
				if (ret_val != -1) 
					std::cout << "Area of rectangle: " << ret_val << std::endl;
				else 
					std::cerr << "Invalid argument" << std::endl;
				break;
			case 3:
				std::cout <<"Enter base: ";
				std::cin >> arg1;
				std::cout <<"Enter the height: ";
				std::cin >> arg2;
				ret_val =  area(arg1, arg2); 
				if (ret_val != -1) 
					std::cout << "Area of triangle: " << ret_val << std::endl;
				else 
					std::cerr << "Invalid argument" << std::endl;
				break;
			case 4:
				std::cout << "Enter side: ";
				std::cin >> arg3;
				ret_val =  area(arg3); 
				if (ret_val != -1) 
					std::cout << "Area of square: " << ret_val<< std::endl;
				else 
					std::cerr << "Invalid argument" << std::endl;
				break;
			default:
				std::cout << "Invalid option" << std::endl;
				break;
		}
	}
	std::cout << "Exiting program...\n";
	return (0);
}

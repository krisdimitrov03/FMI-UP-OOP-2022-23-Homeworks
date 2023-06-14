/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Dimitrov
* @idnumber 8MI0600166
* @task 2
*
*/

#include <iostream>

int main() {
	int number;
	std::cin >> number;

	if (number < 1 || number > 2000) {
		std::cout << "Incorrect input";
		return 0;
	}

	while (number > 0)
	{
		if (number - 1000 >= 0) {
			number -= 1000;
			std::cout << "M";
		}
		else if (number - 500 >= 0) {
			number -= 500;
			std::cout << "D";
		}
		else if (number - 100 >= 0) {
			number -= 100;
			std::cout << "C";
		}
		else if (number - 50 >= 0) {
			number -= 50;
			std::cout << "L";
		}
		else if (number - 10 >= 0) {
			number -= 10;
			std::cout << "X";
		}
		else if (number - 9 >= 0) {
			number -= 9;
			std::cout << "IX";
		}
		else if (number - 5 >= 0) {
			number -= 5;
			std::cout << "V";
		}
		else if (number - 4 >= 0) {
			number -= 4;
			std::cout << "IV";
		}
		else if (number - 1 >= 0) {
			number -= 1;
			std::cout << "I";
		}
	}

	return 0;
}

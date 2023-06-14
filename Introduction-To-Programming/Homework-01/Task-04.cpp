/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Dimitrov
* @idnumber 8MI0600166
* @task 4
*
*/

#include <iostream>

bool isNumberAmazing(int number);
bool isNumberPrime(int number);

int main() {
	int number;
	std::cin >> number;

	if (number < 1 || number > 1000000000) {
		std::cout << "Incorrect input";
		return 0;
	}

	if (isNumberAmazing(number)) {
		std::cout << number;
		return 0;
	}

	int lowerAmazingNum = number - 1, biggerAmazingNum = number + 1;

	while (!(isNumberAmazing(lowerAmazingNum) && isNumberPrime(lowerAmazingNum)))
	{
		lowerAmazingNum--;
	}

	while (!(isNumberAmazing(biggerAmazingNum) && isNumberPrime(biggerAmazingNum)))
	{
		biggerAmazingNum++;
	}

	if (biggerAmazingNum - number < number - lowerAmazingNum)
	{
		std::cout << biggerAmazingNum;
	}
	else
	{
		std::cout << lowerAmazingNum;
	}

	return 0;
}

bool isNumberAmazing(int number)
{
	int outerNumberCopy = number;

	while (outerNumberCopy != 0)
	{
		int outerDigit = outerNumberCopy % 10;
		int count = 0;

		int innerNumberCopy = number;

		while (innerNumberCopy != 0)
		{
			int innerDigit = innerNumberCopy % 10;

			if (innerDigit == outerDigit) {
				count++;
			}

			innerNumberCopy /= 10;
		}

		if (count > 1) {
			return false;
		}

		outerNumberCopy /= 10;
	}

	return true;
}

bool isNumberPrime(int number) {
	if (number == 1 || number == 0) {
		return false;
	}

	for (int i = 2; i < number; i++)
	{
		if (number % i == 0) {
			return false;
		}
	}

	return true;
}

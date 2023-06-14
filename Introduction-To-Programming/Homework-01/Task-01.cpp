/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Dimitrov
* @idnumber 8MI0600166
* @task 1
*
*/

#include <iostream>

int main() {
	int n;
	std::cin >> n;

	if (n < 1 || n > 1000000) {
		std::cout << "Incorrect input";
		return 0;
	}

	int m = 0;

	while (n != 0)
	{
		int digit = n % 10;

		int digitPower2 = digit * digit;

		while (digitPower2 != 0)
		{
			int digitOfDigitPower2 = digitPower2 % 10;
			m += digitOfDigitPower2;

			if (!(n / 10 == 0 && digitPower2 / 10 == 0)) {
				m *= 10;
			}

			digitPower2 /= 10;
		}

		n /= 10;
	}

	std::cout << ++m;

	return 0;
}

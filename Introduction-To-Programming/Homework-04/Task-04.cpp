/**
*
* Solution to homework assignment 4
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

using namespace std;

bool validate(int value) {
	return value >= 1 || value <= 20;
}

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int pour(int fromJug, int toJug, int quantity) {
	int from = fromJug, to = 0;
	int steps = 1;

	while (from != quantity && to != quantity)
	{
		int temp = min(from, toJug - to);
		to += temp;
		from -= temp;
		steps++;

		if (from == quantity || to == quantity)
			break;

		if (from == 0) {
			from = fromJug;
			steps++;
		}

		if (to == toJug) {
			to = 0;
			steps++;
		}
	}

	return steps;
}

int getMinSteps(int m, int n, int k) {
	if (m > n)
		swap(m, n);

	if (k > n)
		return -1;

	if ((k % gcd(n, m)) != 0)
		return -1;

	return min(pour(n, m, k), pour(m, n, k));
}

int main() {
	int n, m, k;
	std::cin >> n >> m >> k;
	if (!validate(n) || !validate(m)) {
		std::cout << "Incorrect input";
		return 0;
	}

	std::cout << getMinSteps(n, m, k);
	return 0;
}

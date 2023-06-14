#include <iostream>
#include "Queue.hpp"

int main()
{
	bool flag = true;

	Queue<char> q(4, flag);

	if (!flag) {
		std::cout << "Invalid priority count in the constructor!";
		return 0;
	}

	q.push('A', 0);
	q.push('B', 3);
	q.push('C', 2);
	q.push('D', 2);
	q.push('E', 1);

	try
	{
		q.push('F', 5);

	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << q.peek() << std::endl; // B
	q.pop();

	std::cout << q.peek() << std::endl; // C
	q.pop();

	std::cout << q.peek() << std::endl; // D
	q.pop();

	std::cout << q.peek() << std::endl; // E
	q.pop();

	std::cout << q.peek() << std::endl; // A
	q.pop();
}
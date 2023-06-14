/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Dimitrov
* @idnumber 8MI0600166
* @task 3
*
*/

#include <iostream>

int main() {
	int n;
	std::cin >> n;
	
	if(n < 2 || n > 9)
	{
		std::cout << "Incorrect input";
		return 0;
	}
	
	//Draws the empty rows before the figure
	for (int i = 0; i < (25 - (2 * n - 1)) / 2; i++)
	{
		std::cout << "\n";
	}
	
	//Draws the upper part of the figure
	for (int i = 1; i <= n; i++)
	{
		//Draws the spaces on the left
		for (int k = 0; k < (80 - 3*n) / 2; k++)
		{
			std::cout << " ";
		}

		//Draws the left part
		for (int j = 1; j <= i; j++)
		{
			std::cout << j;
		}
		//Draws the middle part
		for (int j = 0; j < (2 * (n - i) + n); j++)
		{
			//Checks if the row is the last
			//for this part of the figure
			if (i == n) {
				std::cout << "-";
			}
			else
			{
				std::cout << " ";
			}
		}
		//Draws the right part
		for (int j = i; j > 0; j--)
		{
			std::cout << j;
		}
		
		std::cout << "\n";
	}

	//Draws the bottom part of the figure
	for (int i = n - 1; i >= 1; i--)
	{
		//Draws the spaces on the left
		for (int k = 0; k < (80 - 3*n) / 2; k++)
		{
			std::cout << " ";
		}

		//Draws the left part
		for (int j = 1; j <= i; j++)
		{
			std::cout << j;
		}
		//Draws the middle part
		for (int j = (2 * (n - i) + n); j > 0; j--)
		{
			std::cout << " ";
		}
		//Draws the right part
		for (int j = i; j > 0; j--)
		{
			std::cout << j;
		}
		
		std::cout << "\n";
	}
	
	//Draws the empty rows after the figure
	for (int i = 0; i < (25 - (2 * n - 1)) / 2; i++)
	{
		std::cout << "\n";
	}

	return 0;
}

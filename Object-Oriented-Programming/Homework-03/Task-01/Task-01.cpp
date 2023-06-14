#include <fstream>
#include "ConditionSet.hpp"
#include "IntersectionSet.hpp"
#include "UnionSet.hpp"
#include "External/String.h"


namespace text {
	const char MENU[] = R"(
 Choose from the options below:
 
   [1] Get elements between ... and ...
   [2] Get next element by clicking <Enter>

 Enter option: )";

	const char FILE_NAME[] = "set.dat";
}

String readString(std::ifstream& ifs);

bool dividesNoneOfNumbers(const int& num, const int* arr, size_t length);

bool dividesOneOfNumbers(const int& num, const int* arr, const size_t length);

void printElementsBetween(const int& lhs, const int& rhs, const Set<int>& set);

void generateElements();

Set<int> readSet(std::ifstream& ifs);

int main()
{
	std::ifstream file(text::FILE_NAME, std::ios::in | std::ios::binary);
	/*Set<int> set = readSet<int>(file);*/

	ConditionSet<int> set;
	set.add(4);
	set.add(5);
	set.add(8);
	set.add(9);

	while (1) {
		system("cls"); // this line clears the console
		std::cout << text::MENU;
		int option;
		std::cin >> option;
		std::cin.ignore();

		switch (option) {
		case 1: {
			int left = 0, right = 0;
			std::cin >> left >> right;
			std::cin.ignore();
			printElementsBetween(left, right, set);
			std::cin.get();
			break;
		}
		case 2:
			generateElements();
			break;
		default:
			std::cout << "Invalid option number!" << std::endl;
			std::cout << "Press <Enter> to continue...";
			std::cin.get();
			break;
		}
	}
}

String readString(std::ifstream& ifs) {
	String str = "";
	char character;

	while (ifs.get(character) && character != '\0')
		str += (char*)character;

	return str;
}

bool dividesNoneOfNumbers(const int& num, const int* arr, const size_t length) {
	for (size_t i = 0; i < length; i++)
		if (num % arr[i] == 0)
			return false;

	return true;
}

bool dividesOneOfNumbers(const int& num, const int* arr, const size_t length) {
	size_t devideCount = 0;

	for (size_t i = 0; i < length; i++) {
		if (num % arr[i] == 0)
			devideCount++;

		if (devideCount > 1)
			return false;
	}

	return true;
}

void printElementsBetween(const int& lhs, const int& rhs, const Set<int>& set) {
	for (size_t i = 0; i < set.length(); i++)
	{
		if (set[i] >= lhs && set[i] <= rhs) {
			set.printSingle(set[i]);
			if (i == set.length() - 1)
				std::cout << std::endl;
			else
				std::cout << ", ";
		}
	}
}

void generateElements() {

}

Set<int> readSet(std::ifstream& ifs) {
	if (!ifs.is_open())
		throw std::runtime_error("File could not open!");

	unsigned n = 0, t = 0;

	ifs.read((char*)n, sizeof(unsigned short));
	ifs.read((char*)t, sizeof(unsigned short));

	switch (t) {
	case 0: {
		int* elements = new int[n];

		for (size_t i = 0; i < n; i++)
			ifs.read((char*)elements[i], sizeof(int));

		UnionSet<int>* set = new UnionSet<int>();
		for (size_t i = 0; i < n; i++)
			set->add(elements[i]);

		delete[] elements;

		return (*set);
	}
		  break;
	case 1: {
		int* elements = new int[n];
		for (size_t i = 0; i < n; i++)
			ifs.read((char*)elements[i], sizeof(int));

		ConditionSet<int>* set = new ConditionSet<int>(dividesNoneOfNumbers);

		delete[] elements;
		return *set;
	}
		break;
	case 2: {
		int* elements = new int[n];
		for (size_t i = 0; i < n; i++)
			ifs.read((char*)elements[i], sizeof(int));

		ConditionSet<int>* set = new ConditionSet<int>(dividesOneOfNumbers);

		delete[] elements;
		return *set;
	}
		break;
	case 3: {
		String* filePaths = new String[n];
		for (size_t i = 0; i < n; i++)
			filePaths[i] = readString(ifs);

		Set<int>** sets = new Set<int>*[n];
		for (size_t i = 0; i < n; i++)
		{
			std::ifstream newFile(filePaths[i].c_str(), std::ios::in | std::ios::binary);
			if (!newFile.is_open()) {
				delete[] filePaths;
				delete[] sets;
				throw std::runtime_error("File could not open!");
			}

			Set<int> set = readSet(newFile);
			sets[i++] = &set;
			newFile.close();
		}
		bool isCorrect = true;
		UnionSet<int>* result = new UnionSet<int>((const Set<int>**)sets, n, isCorrect);
		delete[] filePaths;
		delete[] sets;
		return *result;
	}
		break;
	case 4:
		break;
	default:
		throw std::runtime_error("File is not in the correct format!");
			break;
	}

	return ConditionSet<int>();
}
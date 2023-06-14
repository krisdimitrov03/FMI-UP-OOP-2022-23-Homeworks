/**
*
* Solution to homework assignment 4
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

using namespace std;

bool checkIfCorrect(const char* str) {
	int openingBrackets = 0, closingBrackets = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '(')
			openingBrackets++;
		else if (str[i] == ')')
			closingBrackets++;
	}
	return openingBrackets == closingBrackets;
}

bool checkIfClosed(const char* str) {
	int lastOpeningIndex = 0, lastClosingIndex = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '(')
			lastOpeningIndex = i;
		else if (str[i] == ')')
			lastClosingIndex = i;
	}

	return (checkIfCorrect(str) && lastOpeningIndex < lastClosingIndex);
}

int main() {
	char str[257]{ '\0' };
	cin.getline(str, 257);
	char valChar = str[256];
	if (str[256] != '\0') {
		cout << "wrong input";
		return 0;
	}

	bool isCorrect = checkIfCorrect(str);
	bool isClosed = checkIfClosed(str);

	if (isCorrect && isClosed) {
		cout << "correct";
	}
	else {
		cout << "incorrect";
	}
	return 0;
}

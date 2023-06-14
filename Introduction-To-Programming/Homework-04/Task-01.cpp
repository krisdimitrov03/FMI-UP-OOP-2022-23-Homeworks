/**
*
* Solution to homework assignment 4
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
#include <cmath>

using namespace std;

const int MAX_SIZE = 500;

bool isDoubleNum(const char* str) {
    int countOfDelimiters = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            if (str[i] != '.' && str[i] != ',')
                return false;
            if (countOfDelimiters == 0)
                countOfDelimiters++;
            else
                return false;
        }
    }
    return true;
}

double parseToDouble(const char* str) {
    double result = 0.00;
    int i = 0;
    while (str[i] != '.' && str[i] != ',' && str[i] != '\0')
        result = (double)(result * 10 + (str[i++] - '0'));
    i++;
    int p = 1;
    while (str[i] != '\0')
        result += ((double)(str[i++] - '0')) / ((double)pow(10, p++));

    return result;
}

double* getDoubleNumbers(int n, int& length, bool& isEmpty) {
    auto* numbers = new double[n];
    for (int i = 0; i < n; ++i) {
        char str[MAX_SIZE] = { '\0' };
        cin >> str;
        bool isValid = isDoubleNum(str);
        if (!isValid)
            continue;
        numbers[length++] = parseToDouble(str);
    }

    isEmpty = length == 0;
    return numbers;
}

double* sort(double* numbers, int length) {
    int i, j;
    for (i = 0; i < length - 1; i++)
        for (j = 0; j < length - i - 1; j++)
            if (numbers[j] > numbers[j + 1])
                swap(numbers[j], numbers[j + 1]);
    return numbers;
}

int main() {
    int n;
    cin >> n;

    if (n < 3 || n > 50) {
        cout << -1;
        return 0;
    }
    bool isEmpty = true;
    int length = 0;
    double* numbers = getDoubleNumbers(n, length, isEmpty);

    if (isEmpty) {
        cout << "no valid numbers";
    }
    else {
        numbers = sort(numbers, length);
        for (int i = 0; i < length; ++i) {
            cout << ceil(numbers[i] * 100) / 100 << " ";
        }
    }
    return 0;
}

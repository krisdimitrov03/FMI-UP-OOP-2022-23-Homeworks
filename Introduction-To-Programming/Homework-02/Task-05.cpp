/**
*
* Solution to homework assignment 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Dimitrov
* @idnumber 8MI0600166
* @task 5
*
*/

#include <iostream>

static int countOfOperations = 0;
static int minValue = INT16_MAX;

bool IsNumberPrime(int n) {
    if (n == 0 || n == 1)
        return false;

    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int RemoveFirstDigit(int number) {
    countOfOperations++;
    int tmp = number;
    int counter = 1;

    while (number >= 10) {
        counter = 10;
        number /= 10;
    }

    if (number < 10) {
        return (tmp - number * counter);
    } else {
        return 0;
    }
}

int RemoveLastTwoDigits(int number) {
    countOfOperations++;
    int counter = 2;
    while (counter != 0) {
        number /= 10;
        counter--;
    }
    return number;
}

void GetMinOperations(int number) {
    if (number < 2) {
        countOfOperations--;
        return;
    }

    if (IsNumberPrime(number)) {
        if (countOfOperations <= minValue) {
            minValue = countOfOperations;
        }
    } else {

        GetMinOperations(RemoveLastTwoDigits(number));
        GetMinOperations(RemoveFirstDigit(number));
    }
    countOfOperations--;
}

int main() {
    int number;
    std::cin >> number;

    if (number < 1 || number > 1000000000) {
        std::cout << -2;
        return 0;
    }

    GetMinOperations(number);
    std::cout << minValue;
    return 0;
}

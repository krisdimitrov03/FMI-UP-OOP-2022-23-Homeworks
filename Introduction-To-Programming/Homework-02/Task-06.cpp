/**
*  
* Solution to homework assignment 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Dimitrov
* @idnumber 8MI0600166
* @task 6
*
*/

#include <iostream>

long long Pow(int number, int power) {
    long long result = 1;
    for (int i = 0; i < power; ++i) {
        result *= number;
    }

    return result;
}

bool IsInputValid(long long start, long long end) {
    long long maxValue = Pow(2, 31);

    if (start < 1 || start > Pow(2, 31) ||
        end < 1 || end > Pow(2, 31) ||
        start > end) {
        return false;
    }
    return true;
}

bool IsPalindrome(long long number) {
    int digits[1000];
    int counter = 0;

    while (number > 0) {
        int digit = number % 10;
        digits[counter] = digit;
        counter++;
        number /= 10;
    }

    if (counter < 3) {
        return false;
    }

    int reversedDigits[1000];

    for (int i = 0; i < counter; i++) {
        reversedDigits[i] = digits[counter - i - 1];
    }

    for (int i = 0; i < counter; i++) {
        if (digits[i] != reversedDigits[i]) {
            return false;
        }
    }

    return true;
}

bool IsSemiPalindrome(long long number) {
    int digits[1000];
    int countOfDigits = 0, countOfZeros = 0;
    for (int i = 0; number > 0; ++i) {
        int digit = number % 10;
        digits[i] = digit;
        number /= 10;
        countOfDigits++;

        if (digit == 0)
            countOfZeros++;
    }

    if ((countOfDigits < 3) || (countOfZeros > countOfDigits - 2))
        return false;

    int numsOddCount = 0;

    for (int i = 0; i < countOfDigits; ++i) {
        int count = 0;
        for (int j = 0; j < countOfDigits; ++j) {
            if (digits[i] == digits[j]) {
                count++;
            }
        }
        if (count % 2 == 1) {
            numsOddCount++;
        }

        if (numsOddCount > 1) {
            return false;
        }
    }

    return true;
}

int GetPalindromesCount(long long start, long long end) {
    if (!IsInputValid(start, end)) {
        return -1;
    }

    int count = 0;

    for (long long i = start; i <= end; i++) {
        if (IsPalindrome(i) || IsSemiPalindrome(i)) {
            count++;
        }
    }

    return count;
}

int main() {
    int start, end;
    std::cin >> start >> end;
    std::cout << GetPalindromesCount(start, end);

    return 0;
}

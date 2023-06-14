/**
*
* Solution to homework assignment 2
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

const int MAX_SIZE = 1024;

int Int(char value) {
    return (int) (value - '0');
}

void Sum(int *number1, int *number2, int n, int k, bool isNum1Negative, bool isNum2Negative);

void Subtract(int *number1, int *number2, int n, int k, bool isNum1Negative, bool isNum2Negative);

void APlusB(int *a, int *b, int n, int k, char sign);

void AMinusB(int *a, int *b, int n, int k, char sign);

bool IsInputValid(char *num1, char *num2, int n, int k);

bool IsAMoreThanB(int *a, int *b, int n, int k);

void PrintResult(int *number, int length, char sign);

void OperateWithBigNumbers(char *num1, char *num2, int n, int k);

int main() {
    int n, k;
    char num1[MAX_SIZE] = {'\0'}, num2[MAX_SIZE] = {'\0'};
    std::cin >> n >> num1 >> k >> num2;

    OperateWithBigNumbers(num1, num2, n, k);
    return 0;
}

void OperateWithBigNumbers(char *num1, char *num2, int n, int k) {
    if (!IsInputValid(num1, num2, n, k)) {
        std::cout << -1;
        return;
    }

    bool isNum1Negative = num1[0] == '-';
    int number1[MAX_SIZE] = {0};
    bool isNum2Negative = num2[0] == '-';
    int number2[MAX_SIZE] = {0};

    int i;
    int currentLen = isNum1Negative ? n + 1 : n;
    for (i = 0; i < currentLen; ++i) {
        if (currentLen - i - 1 == 0 && isNum1Negative)
            break;

        number1[isNum1Negative ? i - 1 : i] = Int(num1[currentLen - i - 1]);
    }

    currentLen = isNum2Negative ? k + 1 : k;
    for (i = 0; i < currentLen; ++i) {
        if (currentLen - i - 1 == 0 && isNum2Negative)
            break;

        number2[i] = Int(num2[currentLen - i - 1]);
    }

    Sum(number1, number2, n, k, isNum1Negative, isNum2Negative);
    Subtract(number1, number2, n, k, isNum1Negative, isNum2Negative);
}

void Sum(int *number1, int *number2, int n, int k, bool isNum1Negative, bool isNum2Negative) {
    if (!isNum1Negative && isNum2Negative) {
        if (IsAMoreThanB(number2, number1, k, n))
            AMinusB(number2, number1, k, n, '-');
        else
            AMinusB(number1, number2, n, k, '+');
    } else if (isNum1Negative && !isNum2Negative) {
        if (IsAMoreThanB(number2, number1, k, n))
            AMinusB(number2, number1, k, n, '+');
        else
            AMinusB(number1, number2, n, k, '-');
    } else if (isNum1Negative && isNum2Negative) {
        APlusB(number1, number2, n, k, '-');
    } else {
        APlusB(number1, number2, n, k, '+');
    }
}

void Subtract(int *number1, int *number2, int n, int k, bool isNum1Negative, bool isNum2Negative) {
    if (!isNum1Negative && isNum2Negative) {
        APlusB(number1, number2, n, k, '+');
    } else if (isNum1Negative && !isNum2Negative) {
        APlusB(number1, number2, n, k, '-');
    } else if (!isNum1Negative && !isNum2Negative) {
        if (IsAMoreThanB(number2, number1, k, n)) {
            AMinusB(number2, number1, k, n, '-');
        } else {
            AMinusB(number1, number2, n, k, '+');
        }
    } else {
        if (IsAMoreThanB(number1, number2, n, k)) {
            AMinusB(number2, number1, k, n, '-');
        } else {
            AMinusB(number2, number1, k, n, '+');
        }
    }
}

void APlusB(int *a, int *b, int n, int k, char sign) {
    int result[MAX_SIZE + 1] = {0};
    int length = n > k ? n : k;
    int carry = 0, resultCount = 0;

    for (int i = 0; !(i >= length && carry == 0); ++i) {
        int lDigit = a[i];
        int rDigit = b[i];

        int sum = lDigit + rDigit + carry;
        result[i] = sum % 10;
        resultCount++;

        if (sum / 10 != 0) {
            carry = sum / 10;
        } else {
            carry = 0;
        }
    }

    PrintResult(result, resultCount, sign);
}

void AMinusB(int *a, int *b, int n, int k, char sign) {
    int result[MAX_SIZE + 1] = {0};
    int length = n > k ? n : k;
    int borrow = 0, resultCount = 0;

    for (int i = 0; i < length; ++i) {
        int lDigit = a[i];
        int rDigit = b[i];

        int difference = (lDigit - borrow) - rDigit;

        if (i == length - 1 && difference == 0)
            continue;

        if (difference < 0) {
            int digitToAdd = 10 + difference;
            borrow = 1;
            result[resultCount] = digitToAdd;
        } else {
            result[resultCount] = difference;
            borrow = 0;
        }
        resultCount++;
    }

    PrintResult(result, resultCount, sign);
}

void PrintResult(int *number, int length, char sign) {
    if (sign == '-')
        std::cout << sign;

    bool isZero = true;
    for (int i = 0; i < length; ++i) {
        if (number[i] != 0) {
            isZero = false;
            break;
        }
    }

    if (isZero) {
        std::cout << 0 << std::endl;
        return;
    }

    for (int i = 0; i < length; ++i) {
        std::cout << number[length - i - 1];
    }
    std::cout << std::endl;
}

bool IsAMoreThanB(int *a, int *b, int n, int k) {
    if (n > k)
        return true;
    else if (k > n)
        return false;
    else {
        if (a[0] > b[0])
            return true;
        else
            return false;
    }
}

bool IsInputValid(char *num1, char *num2, int n, int k) {
    if (n < 1 || n > 1024)
        return false;
    if (k < 1 || k > 1024)
        return false;
    if ((n == 1024 && num1[0] == '-') || (k == 1024 && num2[0] == '-'))
        return false;

    return true;
}

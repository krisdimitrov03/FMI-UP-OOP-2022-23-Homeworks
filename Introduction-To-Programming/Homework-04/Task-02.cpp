/**
*
* Solution to homework assignment 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Dimitrov
* @idnumber 8MI0600166
* @task 2
*
*/

#include <iostream>

using namespace std;

const int MAX_SIZE = 256;

bool insideString(char value, const char* str, int length) {
    for (int i = 0; i < length; ++i)
        if (value == str[i])
            return true;
    return false;
}

int* getAnagramIndexes(char* str, int n, char* subStr, int k, int& resultLength) {
    int* result = new int[n];
    for (int i = 0; i < n - k + 1; ++i) {
        if (insideString(str[i], subStr, k)) {
            bool areNextInside = true;
            for (int j = 0; j < k; ++j) {
                if (!insideString(str[i + j], subStr, k)) {
                    areNextInside = false;
                    break;
                }
            }

            if (areNextInside)
                result[resultLength++] = i;
        }
    }

    return result;
}

void print(int* arr, int length) {
    for (int i = 0; i < length; ++i) {
        cout << arr[i];
        if (i < length - 1)
            cout << ", ";
    }
}

int len(const char* arr) {
    int length = 0;
    while (arr[length++] != '\0');
    return length - 1;
}

int main() {
    char str[MAX_SIZE] = { '\0' }, subStr[MAX_SIZE] = { '\0' };
    cin >> str >> subStr;

    int strLength = len(str), subStrLength = len(subStr);
    int resultLength = 0;
    int* indexes = getAnagramIndexes(str, strLength, subStr, subStrLength, resultLength);

    if (resultLength == 0) {
        cout << "\"no anagrams\"";
    }
    else {
        print(indexes, resultLength);
        return 0;
    }
}

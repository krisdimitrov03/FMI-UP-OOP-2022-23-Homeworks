/**
*
* Solution to homework assignment 2
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

char ParseToChar(int value) {
    return (char) (value + 48);
}

int StartIndex(const char *arr) {
    int count = 0;
    while (arr[count] != '\0') {
        count++;
    }
    return count;
}

void PrintMember(const char *value) {
    for (int i = 0; value[i] != '\0'; ++i) {
        std::cout << value[i];
    }
}

void CalculateNthMember(int n) {
    if (n < 1 || n > 20) {
        std::cout << -1;
        return;
    }

    char arr[1000] = {'1', '\0'};
    for (int i = 0; i < n - 1; ++i) {
        char currentArr[1000] = {'\0'};
        int count = 0;
        for (int j = 0; arr[j] != '\0'; j += count) {
            char element = arr[j];
            count = 0;
            for (int k = j; arr[k] == element; ++k) {
                count++;
            }
            int startIndex = StartIndex(currentArr);
            currentArr[startIndex] = ParseToChar(count);
            currentArr[startIndex + 1] = element;
        }
        arr[1000] = {'\0'};
        for (int k = 0; currentArr[k] != '\0'; ++k) {
            arr[k] = currentArr[k];
        }
    }
    PrintMember(arr);
}

int main() {
    int n;
    std::cin >> n;
    CalculateNthMember(n);
    
    return 0;
}

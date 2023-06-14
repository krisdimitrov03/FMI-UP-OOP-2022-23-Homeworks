/**
*
* Solution to homework assignment 3
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

const int MAX_SIZE = 15;

void print(int *arr, int length) {
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
}

void swap(int &value1, int &value2) {
    int temp = value1;
    value1 = value2;
    value2 = temp;
}

void getBiggestProjection(int (&arr)[MAX_SIZE], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            int leftTemp = arr[i];
            int rightTemp = arr[j];

            while (leftTemp >= 10)
                leftTemp /= 10;
            while (rightTemp >= 10)
                rightTemp /= 10;

            if (leftTemp < rightTemp) {
                swap(arr[i], arr[j]);
            } else if (leftTemp == rightTemp) {
                leftTemp = arr[i];
                rightTemp = arr[j];

                while (leftTemp > 0 && rightTemp > 0 && leftTemp % 10 == rightTemp % 10) {
                    leftTemp /= 10;
                    rightTemp /= 10;
                }

                if (leftTemp % 10 < rightTemp % 10)
                    swap(arr[i], arr[j]);
            }
        }
    }
}

int main() {
    int n, numbers[MAX_SIZE];
    cin >> n;
    if (n < 1 || n > 15) {
        cout << -1;
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        int number;
        cin >> number;
        if (number < 1 || number > 9999) {
            cout << -1;
            return 0;
        }
        numbers[i] = number;
    }

    getBiggestProjection(numbers, n);
    print(numbers, n);
}

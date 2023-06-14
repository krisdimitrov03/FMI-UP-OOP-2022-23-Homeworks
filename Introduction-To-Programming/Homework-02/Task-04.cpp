/**
*  
* Solution to homework assignment 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Dimitrov
* @idnumber 8MI0600166
* @task 4
*
*/

#include <iostream>

void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int GreatestCommonDevisor(int a, int b) {
    if (b > a)
        Swap(a, b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int CheckIfArrayMagic() {
    int n;
    std::cin >> n;

    if (n < 2 || n > 1024)
        return -1;

    int arr[1024] = {0};
    bool isArrayValid = true;
    for (int i = 0; i < n; ++i) {
        int current;
        std::cin >> current;
        if (current < 1 && current > 1000000000) {
            isArrayValid = false;
            break;
        }
        arr[i] = current;
    }

    if (!isArrayValid)
        return -1;

    int gcd = arr[0];

    for (int i = 0; i < n; ++i) {
        gcd = GreatestCommonDevisor(gcd, arr[i]);
    }

    if (gcd == 1) {
        return 1;
    }
    return 0;
}

int main() {
    std::cout << CheckIfArrayMagic();
    return 0;
}

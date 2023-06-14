/**
*
* Solution to homework assignment 3
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
using namespace std;

int main() {
    char symbol, str[1025] = {'\0'};
    cin >> symbol >> str;

    for (int i = 0; str[i] != '\0'; ++i) {
        str[i] ^= symbol;
        if (str[i] != '\0')
            cout << str[i];
    }
    return 0;
}

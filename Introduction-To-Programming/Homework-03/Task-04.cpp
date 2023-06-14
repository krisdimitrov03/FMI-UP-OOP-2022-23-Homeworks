/**
*
* Solution to homework assignment 3
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

using namespace std;

int pow(int n, int p)
{
    int result = 1;
    for (int i = 0; i < p; i++)
    {
        result *= n;
    }
    return result;
}
bool shouldStop(int arr[], int size) {
    bool firstNumber = false;
    bool secondNumber = false;
    for (int i = 0; i < size; i += 3)
    {
        if (firstNumber && secondNumber) {
            return true;
        }
        if (arr[i] == 0 &&arr[i + 1] == 0 && arr[i + 2] == 0) {
            if (!firstNumber)
                firstNumber = true;
            else
                secondNumber = true;
        }
        else
            firstNumber = false;

    }
    return false;
}
int toDecimal(int bit1, int bit2, int bit3) {
    return bit1 * pow(2, 2) + bit2 * pow(2, 1) + bit3;
}
int main()
{
    int width;
    cin >> width;
    int binaryNums[1027];

    for (int i = 0; i < 1027; i++)
    {
        binaryNums[i] = -1;
    }
    int binaryIndex = 0;
    while (!shouldStop(binaryNums, binaryIndex)) {
        int n;
        cin >> n;
        if (n < 0 || n > 255) {
            cout << "Invalid input";
            return 0;
        }
        int arr[8] = { 0 };
        int index = 7;
        while (n != 0)
        {
            arr[index] = n % 2;
            n /= 2;
            index--;
        }
        for (int i = binaryIndex, j = 0; j < 8; i++, j++)
        {
            binaryNums[i] = arr[j];
        }
        binaryIndex += 8;
    }
    binaryIndex = 0;
    int nums[128];
    int current = 0;
    bool first = true;
    while (binaryNums[binaryIndex] != -1) {
        nums[current] = toDecimal(binaryNums[binaryIndex], binaryNums[binaryIndex + 1], binaryNums[binaryIndex + 2]);
        if (!first && nums[current] == 0 && nums[current - 1] == 0) {
            current++;
            break;
        }
        binaryIndex += 3;
        current++;
        first = false;
    }
    int sumOfNums = 0;
    for (int i = 0; i < current; i++)
    {
        sumOfNums += nums[i];
    }
    if (sumOfNums % width != 0) {
        cout << "Invalid input";
        return 0;
    }

    int charIndex = 0;
    char output[128 * 7];
    for (int i = 0; i < current; i++)
    {
        for (int j = 0; j < nums[i]; j++)
        {
            if (i % 2 == 0) {
                output[charIndex] = '.';
            }
            else {
                output[charIndex] = '#';
            }
            charIndex++;
        }
    }
    for (int i = 0; i < charIndex; i += width)
    {
        for (int j = i; j < i + width; j++)
        {
            cout << output[j];
        }
        cout << endl;
    }
}

/**
*
* Solution to homework assignment 3
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

using namespace std;

const int MAX_SIZE = 10000;

void swap(int &value1, int &value2) {
    int temp = value1;
    value1 = value2;
    value2 = temp;
}

void sort(int *(&arr), int length) {
    for (int i = 0; i < length - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < length; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        if (minIndex != i)
            swap(arr[minIndex], arr[i]);
    }
}

bool insideArray(int value, int *arr, int length) {
    for (int i = 0; i < length; ++i) {
        if (arr[i] == value)
            return true;
    }
    return false;
}

void format(int value, char (&destStr)[5]) {
    int countOfDigits = 0, temp = value;
    while (temp > 0) {
        temp /= 10;
        countOfDigits++;
    }

    for (int i = 0; i < 4 - countOfDigits; ++i)
        destStr[i] = '0';
    for (int i = 0; i < countOfDigits; ++i) {
        destStr[3 - i] = value % 10 + '0';
        value /= 10;
    }
}

int getMinPads(int *arrivals, int *departures, int length) {
    int *all = new int[2 * length];
    int planesArrived = 0, padsNeeded = 0;
    int maxPlanes = 0;
    int maxArrivedPlanesStart = -1;
    int maxArrivedPlanesEnd = -1;

    for (int i = 0; i < length; ++i)
        all[i] = arrivals[i];
    for (int i = 0; i < length; ++i)
        all[i + 6] = departures[i];

    sort(all, 2 * length);

    for (int i = 0; i < 2 * length; ++i) {
        if (insideArray(all[i], arrivals, length)) {
            if (planesArrived + 1 > padsNeeded) {
                padsNeeded++;
            }
            planesArrived++;
            if (planesArrived > maxPlanes) {
                maxPlanes = planesArrived;
                maxArrivedPlanesStart = all[i];
            }
        } else if (insideArray(all[i], departures, length)) {
            if (planesArrived == maxPlanes)
                maxArrivedPlanesEnd = all[i];
            planesArrived--;
        }
    }
    return padsNeeded;
}

void printBusiestPeriods(int *arrivals, int *departures, int length, int maxPlanes) {
    int *all = new int[2 * length];
    for (int i = 0; i < length; ++i)
        all[i] = arrivals[i];
    for (int i = 0; i < length; ++i)
        all[i + length] = departures[i];
    sort(all, 2 * length);

    int periods[MAX_SIZE], planesArrived = 0, periodsCurrentIndex = 0;

    for (int i = 0; i < 2 * length; ++i) {
        if (insideArray(all[i], arrivals, length)) {
            planesArrived++;
            if (planesArrived == maxPlanes) {
                periods[periodsCurrentIndex] = all[i];
                periodsCurrentIndex++;
            }
        } else if (insideArray(all[i], departures, length)) {
            if (planesArrived == maxPlanes) {
                periods[periodsCurrentIndex] = all[i];
                periodsCurrentIndex++;
            }
            planesArrived--;
        }
    }
    for (int i = 0; i < periodsCurrentIndex; i += 2) {
        char start[5] = {'\0'}, end[5] = {'\0'};
        format(periods[i], start);
        format(periods[i + 1], end);
        cout << start << "-" << end << endl;
    }
}

int main() {
    int n;
    cin >> n;
    int *arrivals = new int[n], *departures = new int[n];

    for (int i = 0; i < n; ++i)
        cin >> arrivals[i];
    for (int i = 0; i < n; ++i)
        cin >> departures[i];

    int pads = getMinPads(arrivals, departures, n);
    cout << pads << endl;
    printBusiestPeriods(arrivals, departures, n, pads);
    return 0;
}

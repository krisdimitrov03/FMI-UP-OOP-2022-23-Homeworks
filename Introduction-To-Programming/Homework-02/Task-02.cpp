/**
*  
* Solution to homework assignment 2
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

bool InFace(double x, double y) {
    double r = x * x + y * y;
    return r < 10*10;
}

bool InEye(double x, double y) {
    x = x < 0 ? -1 * x - 4 : x - 4;
    y = y < 0 ? -1 * y - 4 : y - 4;
    double r = x * x + y * y;
    return r < 2*2;
}

bool InNose(double x, double y) {
    double r = x * x + y * y;
    return r < 1;
}

bool InMouth(double x, double y) {
    if (x > -5 && x < 5 &&
        y > -6 && y < -4) {
        return true;
    }
    return false;
}

bool InBackground(double x, double y) {
    if (x > -10 && x < 10 &&
        y > -10 && y < 10) {
        return true;
    }
    return false;
}

bool InBackgroundBorder(double x, double y) {
    if (((x == -10 || x == 10) && y < 10 && y > -10) ||
        ((y == -10 || y == 10) && x < 10 && x > -10)) {
        return true;
    }
    return false;
}

bool InFaceBorder(double x, double y) {
    double r = x * x + y * y;
    return r == 10*10;
}

bool InEyesBorder(double x, double y) {
    x = x < 0 ? -1 * x - 4 : x - 4;
    y = y < 0 ? -1 * y - 4 : y - 4;
    double r = x * x + y * y;
    return r == 2*2;
}

bool InNoseBorder(double x, double y) {
    double r = x * x + y * y;
    return r == 1;
}

bool InMouthBorder(double x, double y) {
    if (((x == -5 || x == 5) && y < -4 && y > -6) ||
        ((y == -4 || y == -6) && x < 5 && x > -5)) {
        return true;
    }
    return false;
}

bool InBorder(double x, double y) {
    if (InBackgroundBorder(x, y) ||
        InFaceBorder(x, y) ||
        InEyesBorder(x, y) ||
        InNoseBorder(x, y) ||
        InMouthBorder(x, y)) {
        return true;
    }
    return false;
}

int main() {
    double x, y;
    std::cin >> x >> y;

    if (InBorder(x, y)) {
        std::cout << "Border";
    } else if (InEye(x, y)) {
        std::cout << "Eye";
    } else if (InNose(x, y)) {
        std::cout << "Nose";
    } else if (InMouth(x, y)) {
        std::cout << "Mouth";
    } else if (InFace(x, y)) {
        std::cout << "Face";
    } else if (InBackground(x, y)) {
        std::cout << "Background";
    } else {
        std::cout << "Miss";
    }

    return 0;
}

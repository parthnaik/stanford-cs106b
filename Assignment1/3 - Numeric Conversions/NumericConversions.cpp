/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    cout << "intToString(-49) = " << intToString(-49) << endl;
    cout << "strToInt(-49) = " << stringToInt("-49") << endl;
    
    return 0;
}

string intToString(int n) {
    if (n >= 0 && n <= 9) {
        return string("") + char('0' + n);
    } else if (n >= 10) {
        return intToString(n / 10) + intToString(n % 10);
    } else {    // if negative integer
        return "-" + intToString(-n);
    }
}

int stringToInt(string str) {
    if (str.length() == 1) {
        return str.at(0) - '0';
    } else if (str.at(0) == '-') {
        return -1 * stringToInt(str.substr(1));
    } else {
        return 10 * (stringToInt(str.substr(0, str.length()-1))) + stringToInt(str.substr(str.length() - 1, 1));
    }
}

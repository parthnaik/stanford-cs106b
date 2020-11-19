/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

int c(int n, int k);

int main() {
    cout << "Hello! This program calculates C(n, k)" << endl;
    int n = getInteger("Enter n: ");
    int k = getInteger("Enter k: ");
    cout << "c(n, k) = " << c(n, k) << endl;
    
    return 0;
}

int c(int n, int k) {
    if (n < 0 || k < 0 || k > n) {  // Invalid Case
        return -1;
    } else if (k == 0 || n == k) {  // Left Ridge and Right Ridge
        return 1;
    } else {
        return c(n - 1, k - 1) + c (n - 1, k);
    }
}

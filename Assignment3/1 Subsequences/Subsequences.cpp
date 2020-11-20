/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    string t = getLine("Please enter a string: ");
    string s = getLine("Please enter a subsequence: ");
    
    if (isSubsequence(t, s)) {
        cout << "The entered subsequence is a substring of the string." << endl;
    } else {
        cout << "The entered subsequence is not a substring of the string." << endl;
    }
    
    return 0;
}

bool isSubsequence(string text, string subsequence) {
    // Base Case 0 (if subsequence is an empty string):
    if (subsequence == "") {
        return true;
    }
    
    // Base Case 1 (if subsequence is not empty and text is empty):
    if (text == "") {
        return false;
    }
    
    if (subsequence[0] == text[0]) {
        return isSubsequence(text.substr(1), subsequence.substr(1));
    } else {
        return isSubsequence(text.substr(1), subsequence);
    }
    
    return false;
}

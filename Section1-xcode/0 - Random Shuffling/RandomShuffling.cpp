/*
 * File: RandomShuffling.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

string randomShuffle(string input);

int main() {
    string input;
    
    cout << "Enter string to shuffle" << endl;
    cin >> input;
    
    cout << "The shuffled string is: " << randomShuffle(input) << endl;
    
    return 0;
}

string randomShuffle(string input) {
    if (input == "") {
        return input;
    } else {
        int i = randomInteger(0, input.length() - 1);
        return input[i] + randomShuffle(input.substr(0, i) + input.substr(i + 1));
    }
}
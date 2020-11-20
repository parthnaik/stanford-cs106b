/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "random.h"
#include "console.h"
using namespace std;

/* Constants */
const int HEADS = 0;
const int TAILS = 1;

int main() {
    int flips = 0;
    int consecHeads = 0;
    
    while (true) {
        int random = randomInteger(0, 1);
        flips++;
        
        if (random == HEADS) {
            cout << "Heads" << endl;
            consecHeads++;
        }
        
        if (random == TAILS) {
            consecHeads = 0;
            cout << "Tails" << endl;
        }
        
        if (consecHeads == 3) {
            cout << "It took " << flips << " flips to get 3 consecutive heads." << endl;
            break;
        }
    }
    
    return 0;
}

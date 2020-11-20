/*
 * File: CHeMoWIZrDy.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
using namespace std;

const int MAX_SYMBOL_SIZE = 3;

bool isElementSpellable(string text, Lexicon& symbol);

int main() {
    
    return 0;
}

bool isElementSpellable(string text, Lexicon& symbol) {
    // Base Case 0 (if there is no text at all):
    if (text == "") return true;
    
    for (int i = 1; i <= text.size() && i <= MAX_SYMBOL_SIZE; i++) {
        if (symbol.contains(text.substr(0, i)) && isElementSpellable(text.substr(i), symbol)) {
            return true;
        }
    }
    
    return false;
}

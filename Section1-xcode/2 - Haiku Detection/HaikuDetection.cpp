/*
 * File: HaikuDetection.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "tokenscanner.h"
using namespace std;

bool isHaiku(string line1, string line2, string line3);
int syllablesInLine(string line);
bool isVowel(char c);
int syllablesInWord(string word);

int main() {
    string line1 = getLine("Enter first line: ");
    string line2 = getLine("Enter second line: ");
    string line3 = getLine("Enter third line: ");
    
    if (isHaiku(line1, line2, line3)) {
        cout << "The text you entered is a haiku!" << endl;
    } else {
        cout << "The text you entered is NOT a haiku!" << endl;
    }
    
    return 0;
}

bool isHaiku(string line1, string line2, string line3) {
    return syllablesInLine(line1) == 5 && syllablesInLine(line2) == 7 && syllablesInLine(line3) == 5;
}

int syllablesInLine(string line) {
    TokenScanner scanner(line);
    scanner.ignoreWhitespace();
    scanner.addWordCharacters(",'");
    
    int numSyllables = 0;
    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (scanner.getTokenType(token) == WORD) {
            numSyllables += syllablesInWord(token);
        }
    }
    
    return numSyllables;
}

int syllablesInWord(string token) {
    int count = 0;
    
    if (token[token.length() - 1] == '!' || token[token.length() - 1] == ',') {
        token = token.substr(0, token.length() - 1);
    }
    
    for (int i = 0; i < token.length(); i ++) {
        if (isVowel(token[i])) {
            if (i != 0 && isVowel(token[i - 1])) {
                continue;
            }
            if ((i == token.length() - 1) && (token[i] == 'e' || token[i] == 'E')) {
                continue;
            }
            
            count++;
        }
    }
    
    if (count == 0) return 1;
    return count;
}

bool isVowel(char ch) {
    if (ch == 'a' || ch == 'A') return true;
    if (ch == 'e' || ch == 'E') return true;
    if (ch == 'i' || ch == 'I') return true;
    if (ch == 'o' || ch == 'O') return true;
    if (ch == 'u' || ch == 'U') return true;
    if (ch == 'y' || ch == 'Y') return true;
    
    return false;
}
/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "tokenscanner.h"
#include "simpio.h"
using namespace std;

/* Constants */
const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;

void openFile(ifstream& fin);
bool isVowel(char c);
bool isEndOfSentence(string token);
int countSyllables(string token);
int computeFleschKincaid(int wordCount, int syllableCount, int sentenceCount);

int main() {
    ifstream fin;
    TokenScanner scanner;
    int wordCount = 0;
    int syllableCount = 0;
    int sentenceCount = 0;
    
    openFile(fin);
    scanner.setInput(fin);
    scanner.ignoreWhitespace();
    scanner.addWordCharacters("'");
    
    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        
        if (scanner.getTokenType(token) == WORD) {
            wordCount++;
            syllableCount += countSyllables(token);
        } else if (isEndOfSentence(token)) {
            sentenceCount++;
        }
    }
    
    if (wordCount == 0) wordCount = 1;
    if (sentenceCount == 0) sentenceCount = 1;
    
    cout << "Words: " << wordCount << endl;
    cout << "Syllables: " << syllableCount << endl;
    cout << "Sentences: " << sentenceCount << endl;
    cout << "Grade Level: " << computeFleschKincaid(wordCount, syllableCount, sentenceCount) << endl;
    
    return 0;
}

void openFile(ifstream& fin) {
    string filename;
    
    while (true) {
        filename = getLine("Enter the source text: ");
        fin.open(filename.c_str());
        
        if (fin.fail()) {
            cout << "Could not open file." << endl;
            fin.clear();
        } else {
            break;
        }
    }
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

bool isEndOfSentence(string token) {
    if (token.length() != 1) {
        return false;
    }
    
    if (token[0] == '.' || token[0] == '?' || token[0] == '!') {
        return true;
    }
    
    return false;
}

int countSyllables(string token) {
    int count = 0;
    
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

int computeFleschKincaid(int wordCount, int syllableCount, int sentenceCount) {
    return C0 + C1 * ((double)wordCount / sentenceCount) + C2 * ((double)syllableCount / wordCount);
}
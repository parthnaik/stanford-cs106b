/*
 * File: GeneratingMultiwordAnagrams.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "vector.h"
#include "lexicon.h"
#include "console.h"
#include "simpio.h"
using namespace std;

const int MIN_WORD_SIZE = 3;

bool findAnagram(string letters, Lexicon& english, Vector<string>& words);
bool findAnagramWithFixedPrefix(string prefix, string rest, Lexicon& english, Vector<string>& words);

int main() {
    Lexicon dictionary("EnglishWords.dat");
    dictionary.add("");
    string userInput = getLine("Enter a string to find the anagram of: ");
    Vector<string> foundWords;
    
    if (findAnagram(userInput, dictionary, foundWords)) {
        foreach (string w in foundWords) {
            cout << w + " ";
        }
        
        cout << endl;
    } else {
        cout << "No anagrams were found." << endl;
    }
    
    return 0;
}

bool findAnagram(string letters, Lexicon& english, Vector<string>& words) {
    return findAnagramWithFixedPrefix("", letters, english, words);
}

bool findAnagramWithFixedPrefix(string prefix, string rest, Lexicon& english, Vector<string>& words) {
    if (!english.contains(prefix)) return false;
    
    if (english.contains(prefix) && prefix.length() >= MIN_WORD_SIZE) {
        if (rest == "" || findAnagram(rest, english, words)) {
            words.add(prefix);
            return true;
        }
    }
    
    for (int i = 0; i < rest.length(); i++) {
        string otherLetters = rest.substr(0, i) + rest.substr(i + 1);
        if (findAnagramWithFixedPrefix(prefix + rest[i], otherLetters, english, words)) return true;
    }
    
    return false;
}

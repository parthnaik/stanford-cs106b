/*
 * File: XzibitWords.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
using namespace std;

string mostXzibitWord(Lexicon& words);
Map<string, Vector<string> > generateMap(Lexicon& words);
Vector<string> findXzibitWords(string word, Lexicon& words);

int main() {
    Lexicon dictionary("EnglishWords.dat");
    
    cout << "Processing..." << endl;
    cout << "The most Xzibit word is " << mostXzibitWord(dictionary) << endl;
    
    return 0;
}

string mostXzibitWord(Lexicon& words) {
    Map<string, Vector<string> > map = generateMap(words);
    string answer;
    int xzibitCount = 0;
    
    foreach(string word in words) {
        if (map[word].size() > xzibitCount) {
            xzibitCount = map[word].size();
            answer = word;
        }
    }
    
    return answer;
}

Map<string, Vector<string> > generateMap(Lexicon& words) {
    Map<string, Vector<string> > xzibitMap;
    
    foreach (string word in words) {
        xzibitMap[word] = findXzibitWords(word, words);
    }
    
    return xzibitMap;
}

Vector<string> findXzibitWords(string word, Lexicon& words) {
    Vector<string> result;
    string partial;
    int len = word.length();
    
    for (int i = 0; i < word.length(); i++) {
        for (int j = 0; j <= i; j++) {
            partial = word.substr(j, len);
            if (words.contains(partial)) {
                result.add(partial);
            }
        }
        len--;
    }
    
    return result;
}
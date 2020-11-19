/*
 * File: WordLadder.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

/* Constants */
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

Vector<string> getNextWords(string word, Lexicon& dictionary);
void displaySolution(Vector<string>& answer);
bool isValidInput(string start, string target, Lexicon& dictionary);
bool isUsed(string word, Vector<string>& usedWords);

int main() {
    Lexicon dictionary("EnglishWords.dat");
    
    while (true) {
        
        string start;
        string target;
        Vector<string> usedWords;
        Vector<string> ladder;
        Queue<Vector<string> > allLadders;
        
        start = getLine("Enter the starting word (or nothing to quit): ");
        if (start == "") break;
        target = getLine("Enter the ending word: ");
        
        // Initialize with the start word
        cout << "Searching..." << endl;
        ladder.add(start);
        usedWords.add(start);
        allLadders.enqueue(ladder);
        ladder.clear();
        
        while (!allLadders.isEmpty()) {
            if (isValidInput(start, target, dictionary)) {
                Vector<string> currentLadder = allLadders.dequeue();
                string lastWord = currentLadder[currentLadder.size() - 1];
                
                if (lastWord == target) {
                    ladder = currentLadder;
                    break;
                }
                
                Vector<string> nextWords = getNextWords(lastWord, dictionary);
                
                for (int i = 0; i < nextWords.size(); i++) {
                    if (!isUsed(nextWords[i], usedWords)) {
                        Vector<string> nextLadder = currentLadder;
                        nextLadder.add(nextWords[i]);
                        allLadders.enqueue(nextLadder);
                        usedWords.add(nextWords[i]);
                    }
                }
            } else {
                allLadders.clear();
            }
        }
        
        displaySolution(ladder);
    }
    
    return 0;
}

Vector<string> getNextWords(string word, Lexicon& dictionary) {
    Vector<string> nextWords;
    
    if (!dictionary.contains(word)) {
        return nextWords;
    }
    
    for (int i = 0; i < word.length(); i++) {
        for (int j = 0; j < ALPHABET.length(); j++) {
            string newWord = word;
            newWord[i] = ALPHABET[j];
            if (newWord != word && dictionary.contains(newWord)) nextWords.add(newWord);
        }
    }
    
    return nextWords;
}

void displaySolution(Vector<string>& answer) {
    if (answer.isEmpty()) {
        cout << "No solution found." << endl << endl;
    } else {
        for (int i = 0, s = answer.size(); i < s; i++) {
            if (i == s - 1) {
                cout << answer[i];
            } else {
                cout << answer[i] << " -> ";
            }
        }
        cout << endl << endl;
    }
}

bool isValidInput(string start, string target, Lexicon& dictionary) {
    if (start.length() != target.length()) return false;
    if (!dictionary.contains(start)) return false;
    if (!dictionary.contains(target)) return false;
    return true;
}

bool isUsed(string word, Vector<string>& usedWords) {
    for (int i = 0; i < usedWords.size(); i++) {
        if (usedWords[i] == word) return true;
    }
    
    return false;
}
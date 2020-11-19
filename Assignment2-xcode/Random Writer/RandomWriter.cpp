/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "vector.h"
#include "map.h"
#include "simpio.h"
#include "random.h"
using namespace std;

/* Constants */
const int NUM_CHARS = 2000;

void openFile(ifstream& fin);
Map<string, Vector<char> > analyzeText(ifstream& fin, int markovOrder);
string findInitialSeed(Map<string, Vector<char> > map);

int main() {
    int order;
    ifstream fin;
    Map<string, Vector<char> > analysisMap;
    string initialSeed;
    string currentSeed;
    int outputTextSize;
    char nextChar;
    
    openFile(fin);
    while (true) {
        order = getInteger("Enter the Markov order [1-10]: ");
        if (order >= 1 && order <= 10) {
            break;
        } else {
            cout << "Error: Order out of range." <<endl;
        }
    }
    
    cout << "Processing File..." << endl;
    
    analysisMap = analyzeText(fin, order);
    initialSeed = findInitialSeed(analysisMap);
    
    cout << initialSeed;
    currentSeed = initialSeed;
    outputTextSize = initialSeed.size();
    
    while (outputTextSize < NUM_CHARS) {
        if (!analysisMap.containsKey(currentSeed) || analysisMap[currentSeed].size() == 0) break;
        nextChar = analysisMap[currentSeed][randomInteger(0, analysisMap[currentSeed].size() - 1)];
        cout << nextChar;
        currentSeed = currentSeed.substr(1) + nextChar;
        outputTextSize++;
    }
    
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

Map<string, Vector<char> > analyzeText(ifstream& fin, int markovOrder) {
    Map<string, Vector<char> > frequencies;
    char ch;
    string word;
    int chCount = 0;
    
    while (fin.get(ch)) {
        if (chCount != markovOrder) {
            word += ch;
            chCount++;
        } else {
            frequencies[word].add(ch);
            word = word.substr(1) + ch;
        }
    }
    
    return frequencies;
}

string findInitialSeed(Map<string, Vector<char> > map) {
    string initialSeed;
    int frequency = 0;
    
    foreach (string key in map) {
        if (map[key].size() > frequency) {
            frequency = map[key].size();
            initialSeed = key;
        }
    }
    
    return initialSeed;
}
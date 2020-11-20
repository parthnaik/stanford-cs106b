/*
 * File: ComputingAverages.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include <fstream>
#include "console.h"
using namespace std;

void averageValueInFile(string filename, double& result);

int main() {
    double result;
    string filename;
    cout << "Enter input filename: " << endl;
    cin >> filename;
    
    averageValueInFile(filename, result);
    cout << "The average is: " << result << endl;
    
    return 0;
}

void averageValueInFile(string filename, double& result) {
    ifstream fin;
    double val;
    result = 0;
    int numValues = 0;
    
    fin.open(filename.c_str());
    
    while (fin >> val) {
        result += val;
        numValues++;
    }
    
    result = result / numValues;
}

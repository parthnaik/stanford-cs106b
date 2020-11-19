/*
 * File: TwoRNAProteinCodes.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include <string>
#include "vector.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

Vector<string> findProteins(string rna, Map<string, string>& codons);

int main() {
    Map<string, string> codons;
    
    codons["GGG"] = "Glycine";
    codons["AUG"] = "Methionine";
    codons["AAU"] = "Asparagine";
    codons["AUC"] = "Isoleucine";
    codons["UCG"] = "Serine";
    codons["GCG"] = "Alanine";
    codons["GAU"] = "Aspartic Acid";
    codons["AGA"] = "Arginine";
    codons["CGA"] = "Arginine";
    codons["CUA"] = "Leucine";
    codons["AUA"] = "Isoleucine";
    codons["GGA"] = "Glycine";
    codons["UCA"] = "Serine";
    codons["CCG"] = "Proline";
    codons["CCU"] = "Proline";
    codons["UAA"] = "stop";
    codons["UAG"] = "stop";
    codons["UGA"] = "stop";
    
    string rna = getLine("Enter RNA string: ");
    Vector<string> result = findProteins(rna, codons);
    
    foreach (string c in result) {
        cout << c << endl;
    }
    
    return 0;
}

Vector<string> findProteins(string rna, Map<string, string>& codons) {
    Vector<string> result;

    int index = 0;
    while (true) {
        index = rna.find("AUG", index);
        if (index == string::npos) {
            return result;
        }

        string protein;
        while (true) {
            string codon = rna.substr(index, 3);
            index += 3;

            if (codons[codon] == "stop") break;

            if (!protein.empty()) protein += ", ";
            protein += codons[codon];
        }

        result += protein;
    }
}
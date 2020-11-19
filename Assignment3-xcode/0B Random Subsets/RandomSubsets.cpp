/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
using namespace std;

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
Set<int> randomSubsetOf(Set<int>& s);

int main() {
    Set<int> testSet;
    
    testSet += 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    cout << randomSubsetOf(testSet) << endl;
    
    return 0;
}

Set<int> randomSubsetOf(Set<int>& s) {
    /* Base Case 0 (if set is empty): */
    if (s.isEmpty()) return s;
    
    /* Extract the first element from the set */
    int elem = s.first();
    
    /* Compute a random subset of what remains. Remove first element, compute random set and put element back in */
    s -= elem;
    Set<int> result = randomSubsetOf(s);
    s += elem;
    
    /* Randomly choose whether to add the element back in */
    return randomChance(0.5) ? result : result + elem;
}

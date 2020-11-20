/*
 * File: WeightsAndBalances.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "vector.h"
#include "console.h"
#include "simpio.h"
using namespace std;

bool isMeasurable(int target, Vector<int>& weights);

int main() {
    Vector<int> weights;
    int target = getInteger("Enter target weight: ");
    
    while (true) {
        int wt = getInteger("Enter sample weight (-1 to stop): ");
        if (wt < 0) break;
        weights.add(wt);
    }
    
    if (isMeasurable(target, weights)) {
        cout << "The target is measurable using the given weights." << endl;
    } else {
        cout << "The target is not measurable using the given weights." << endl;
    }
    
    return 0;
}

/*
 * 1. The first weight is unused. In this case, it is possible to measure the target only if is it
 * possible to do so using the rest of the weights.
 *
 * 2. The first weight goes on the opposite side of the sample. In this case, the target is effectively
 * reduced by the first, therefore it is possible to measure only if target - first is measurable
 * by the rest of the weights.
 *
 * 3. The first weight goes on the same side as the target. In this case, the target can only be measured if
 * target + first can be measured by rest.
 */

bool isMeasurable(int target, Vector<int>& weights) {
    if (weights.isEmpty()) {
        return target == 0;
    }
    
    int first = weights[0];
    Vector<int> rest = weights;
    rest.remove(0);
    
    return isMeasurable(target, rest) || isMeasurable(target - first, rest) || isMeasurable(target + first, rest);
}

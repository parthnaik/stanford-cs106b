/*
 * File: FillingARegion.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "grid.h"
#include "console.h"
using namespace std;

void fillRegion(Grid<bool>& pixels, int row, int col);

int main() {
    
    return 0;
}

void fillRegion(Grid<bool>& pixels, int row, int col) {
    if (pixels.inBounds(row, col) && !pixels[row][col]) {
        pixels[row][col] = true;
        fillRegion(pixels, row + 1, col);
        fillRegion(pixels, row - 1, col);
        fillRegion(pixels, row, col + 1);
        fillRegion(pixels, row, col - 1);
    }
}



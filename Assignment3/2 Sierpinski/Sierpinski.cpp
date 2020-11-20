/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

const double WINDOW_SIZE = 800;

void sierpinski(GWindow gw, GPoint pt, double length, int order);
void drawTriangle(GWindow gw, GPoint pt, double length);

int main() {
    double length = getReal("Please enter side length: ");
    int order = getInteger("Please enter fractal order: ");
    
    double halfPerimeter = 3 * length / 2;
    double area = sqrt(halfPerimeter * pow((halfPerimeter - length), 3));
    double height = 2 * area / length;
    
    GWindow gw(WINDOW_SIZE, WINDOW_SIZE);
    GPoint start(WINDOW_SIZE / 2 - length / 2, WINDOW_SIZE / 2 + height / 2);
    sierpinski(gw, start, length, order);
    
    return 0;
}

void sierpinski(GWindow gw, GPoint pt, double length, int order) {
    if (order == 0) {
        drawTriangle(gw, pt, length);
        return;
    }
    
    sierpinski(gw, pt, length / 2, order - 1); // draw left triangle
    sierpinski(gw, GPoint(pt.getX() + length / 2, pt.getY()), length / 2, order - 1); // draw right triangle
    sierpinski(gw, GPoint(pt.getX() + length / 4, pt.getY() - length / 2), length / 2, order - 1); // draw top triangle
}

void drawTriangle(GWindow gw, GPoint pt, double length) {
    pt = gw.drawPolarLine(pt, length, 0);
    pt = gw.drawPolarLine(pt, length, 120);
    pt = gw.drawPolarLine(pt, length, -120);
}



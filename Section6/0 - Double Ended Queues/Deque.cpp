/*
 * File: Deque.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "console.h"
#include "error.h"
#include "Deque.h"

int main() {
    Deque d;
    
    d.pushFront(3);
    d.pushFront(5);
    d.pushBack(8);
    d.popBack();
    d.popFront();
    
    d.printDeque();
    
    return 0;
}

Deque::Deque() {
    head = tail = NULL;
}

Deque::~Deque() {
    while (head != NULL) {
        Cell* next = head->next;
        delete head;
        head = next;
    }
}

/* Adds a value to the front or the back of the deque. */
void Deque::pushFront(int value) {
    Cell* cell = new Cell;
    cell->value = value;
    
    cell->next = head;
    cell->prev = NULL;
    
    if (head == NULL) {
        head = tail = cell;
    } else {
        head->prev = cell;
        head = cell;
    }
}

void Deque::pushBack(int value) {
    Cell *cell = new Cell;
    cell->value = value;
    
    cell->prev = tail;
    cell->next = NULL;
    
    if (head == NULL) {
        head = tail = cell;
    } else {
        tail->next = cell;
        tail = cell;
    }
}

/* Returns and removes the first or last element of the deque. */
int Deque::popFront() {
    if (head == NULL) error("That which does not exist cannot be popped.");
    
    int result = head->value;
    Cell* toRemove = head;
    
    head = head->next;
    
    if (head != NULL) {
        head->prev = NULL;
    } else {
        tail = NULL;
    }
    
    delete toRemove;
    
    return result;
}

int Deque::popBack() {
    if (tail == NULL) error("That which does not exist cannot be popped.");
    
    int result = tail->value;
    Cell* toRemove = tail;
    
    tail = tail->prev;
    
    if (tail != NULL) {
        tail->next = NULL;
    } else {
        head = NULL;
    }
    
    delete toRemove;
    
    return result;
}

/* Prints the deque's contents */
void Deque::printDeque() {
    if (head == NULL) cout << "Deque is empty" << endl;
    
    Cell* cell = head;
    
    while (cell != NULL) {
        cout << cell->value << " ";
        cell = cell->next;
    }
    
    cout << endl;
}
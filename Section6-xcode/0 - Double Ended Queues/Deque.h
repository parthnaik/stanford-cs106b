/**********************************************
 * File: DoubleEndedQueues.h
 *
 * A file containing the types used by the double
 * ended queue program.
 */

#ifndef Deque_h
#define Deque_h

#include <string>
using namespace std;

class Deque {
public:
    /* Constructor for the double ended queue */
    Deque();
    
    /* Destructor for the double ended queue */
    ~Deque();
    
    /* Adds a value to the front or the back of the deque. */
    void pushFront(int value);
    void pushBack(int value);
    
    /* Returns and removes the first or last element of the deque. */
    int popFront();
    int popBack();
    
    /* Prints the deque's contents */
    void printDeque();
    
private:
    struct Cell {
        int value;
        Cell* next;
        Cell* prev;
    };
    Cell* head;
    Cell* tail;
};

#endif

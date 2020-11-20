/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
    head = NULL;
    listSize = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    while (head != NULL) {
        Cell* next = head->next;
        delete head;
        head = next;
    }
}

int LinkedListPriorityQueue::size() {
    return listSize;
}

bool LinkedListPriorityQueue::isEmpty() {
    return listSize == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
    Cell* n = new Cell;
    n->value = value;
    
    if (isEmpty()) {
        head = n;
    } else {
        for (Cell* curr = head; curr != NULL; curr = curr->next) {
            Cell* next = curr->next;
            
            if (curr == head && n->value < head->value) {
                n->next = head;
                head = n;
                break;
            }
            
            if (next == NULL) {
                curr->next = n;
                break;
            }
            
            if (n->value < next->value) {
                n->next = next;
                curr->next = n;
                break;
            }
        }
    }
    
    listSize++;
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty()) error("The queue is empty.");
	
    return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) error("The queue is empty.");
    
    Cell* min = head;
    head = head->next;
    string minVal = min->value;
    delete min;
    listSize--;
	
	return minVal;
}


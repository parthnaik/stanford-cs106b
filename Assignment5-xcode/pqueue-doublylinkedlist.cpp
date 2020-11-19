/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    head = NULL;
    listSize = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    while (head != NULL) {
        Cell* next = head->next;
        delete head;
        head = next;
    }
}

int DoublyLinkedListPriorityQueue::size() {
    return listSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
    return listSize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    Cell* n = new Cell;
    n->value = value;
    
    if (isEmpty()) {
        head = n;
    } else {
        head->prev = n;
        n->next = head;
        head = n;
    }
    
    listSize++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) error("The queue is empty.");
    
    string min;
    getFirst(min);
	
	return min;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) error("The queue is empty.");
	
    string min;
    getFirst(min);
    Cell* first;
    
    for (first = head; first != NULL; first = first->next) {
        if (first->value == min) {
            break;
        }
    }
    
    if (listSize == 1) {
        delete head;
        head = NULL;
    } else {
        if (first->prev == NULL) {
            head = first->next;
        }
        
        if (first->prev != NULL) {
            first->prev->next = first->next;
        }
        
        if (first->next != NULL) {
            first->next->prev = first->prev;
        }
        
        delete first;
    }
    
    listSize--;
    
	return min;
}

void DoublyLinkedListPriorityQueue::getFirst(string& min) {
    min = head->value;
    
    for (Cell* curr = head; curr != NULL; curr = curr->next) {
        if (curr->value < min) {
            min = curr->value;
        }
    }
}

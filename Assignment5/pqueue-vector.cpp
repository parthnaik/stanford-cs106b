/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	
}

VectorPriorityQueue::~VectorPriorityQueue() {
	
}

int VectorPriorityQueue::size() {
    return pQueue.size();
}

bool VectorPriorityQueue::isEmpty() {
    return pQueue.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
    pQueue.add(value);
}

string VectorPriorityQueue::peek() {
    if (isEmpty()) error("The queue is empty.");
    
    int first = getFirst();
    string el = pQueue.get(first);
	
	return el;
}

string VectorPriorityQueue::dequeueMin() {
	if (isEmpty()) error("The queue is empty.");
    
    int first = getFirst();
    string el = pQueue.get(first);
    pQueue.remove(first);
	
	return el;
}

int VectorPriorityQueue::getFirst() {
    int f = 0;
    
    for (int i = 0; i < size(); i++) {
        if (pQueue[i] < pQueue[f]) {
            f = i;
        }
    }
    
    return f;
}

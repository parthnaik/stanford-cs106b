/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */

#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
    pQueue = new string[INITIAL_CAPACITY + 1];
    capacity = INITIAL_CAPACITY;
    numAllocated = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] pQueue;
}

int HeapPriorityQueue::size() {
    return numAllocated;
}

bool HeapPriorityQueue::isEmpty() {
    return numAllocated == 0;
}

void HeapPriorityQueue::enqueue(string value) {
    if (numAllocated == capacity) grow();
    pQueue[++numAllocated] = value;
    bubbleUp(numAllocated);
}

string HeapPriorityQueue::peek() {
    if (isEmpty()) error("The queue is empty.");
    
    return pQueue[1];
}

string HeapPriorityQueue::dequeueMin() {
    if (isEmpty()) error("The queue is empty.");
    
    string min = pQueue[1];
    pQueue[1] = pQueue[numAllocated];
    numAllocated--;
    bubbleDown(1);
    
    return min;
}

void HeapPriorityQueue::grow() {
    capacity *= 2;
    string* newPQueue = new string[capacity + 1];
    
    for (int i = 0; i <= numAllocated; i++) {
        newPQueue[i] = pQueue[i];
    }
    
    delete[] pQueue;
    pQueue = newPQueue;
}

void HeapPriorityQueue::bubbleUp(int index) {
    while (index > 1) {
        if (pQueue[index / 2] > pQueue[index]) {
            swap(pQueue[index / 2], pQueue[index]);
            index /= 2;
        } else {
            break;
        }
    }
}

void HeapPriorityQueue::bubbleDown(int parent) {
    int leftChild = 2 * parent;
    int rightChild = 2 * parent + 1;

    // If no children
    if (leftChild > numAllocated) return;

    // If parent less than equal both children no swap needed
    if (pQueue[parent] <= pQueue[leftChild]) {
        if (rightChild > numAllocated) return;
        if (pQueue[parent] <= pQueue[rightChild])  return;
    }

    int smaller = leftChild;
    if (pQueue[rightChild] < pQueue[leftChild]) smaller = rightChild;
    swap(pQueue[parent], pQueue[smaller]);
    bubbleDown(smaller);
}

void HeapPriorityQueue::swap(string& a, string& b) {
    string temp = a;
    a = b;
    b = temp;
}
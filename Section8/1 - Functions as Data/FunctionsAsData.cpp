/*
 * File: FunctionsAsData.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "queue.h"
#include "console.h"
using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;
};

void breadthFirstSearch(Node* root, void processFn(Node* node));

int main() {

    return 0;
}

void breadthFirstSearch(Node* root, void processFn(Node* node)) {
    Queue<Node*> workList;
    workList.enqueue(root);
    
    while (!workList.isEmpty()) {
        Node* curr = workList.dequeue();
        
        if (curr != NULL) {
            processFn(curr);
            
            workList.enqueue(curr->left);
            workList.enqueue(curr->right);
        }
    }
}

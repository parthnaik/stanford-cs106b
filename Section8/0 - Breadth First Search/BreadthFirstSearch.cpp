/*
 * File: BreadthFirstSearch.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "console.h"
#include "queue.h"
using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;
};

void breadthFirstSearch(Node* root);

int main() {
    
    return 0;
}

void breadthFirstSearch(Node* root) {
    Queue<Node*> workList;
    workList.enqueue(root);
    
    while (!workList.isEmpty()) {
        Node* curr = workList.dequeue();
        if (curr != NULL) {
            cout << curr->value << endl;
            
            workList.enqueue(curr->left);
            workList.enqueue(curr->right);
        }
    }
}
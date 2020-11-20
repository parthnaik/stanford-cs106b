/*
 * File: CheckingBSTValidity.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "console.h"
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

bool isBST(Node* root);

int main() {
    
    return 0;
}

bool isBST(Node* root) {
    if (root == NULL) return true;
    
    if (root->left != NULL && root->left->value > root->value) {
        return false;
    }
    
    if (root->right != NULL && root->right->value < root->value) {
        return false;
    }
    
    if (!isBST(root->left) || !isBST(root->right)) {
        return false;
    }
    
    return true;
}

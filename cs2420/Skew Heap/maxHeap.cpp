//
//  maxHeap.cpp
//  Skew Heap
//
//  Created by Steven Proctor on 11/3/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "maxHeap.hpp"

//Constructor
maxHeap::maxHeap() {
    numMerges = 0;
    root = NULL;
    size = 0;
}

//Destructor
maxHeap::~maxHeap() {
    
}

//Create new node, merge into heap
//Returns the inserted value for debug purposes
int maxHeap::insert(int newVal) {
    
    Node * newNode = new Node;
    newNode->key = newVal;
    newNode->left = NULL;
    newNode->right = NULL;
    
    root = merge(root, newNode);
    size++;
    
    return newVal;
}

//Delete the root of the heap
//Returns deleted value
int maxHeap::deleteMax() {
    
    if (!root) {return -1;}
    
    int deletedNum = root->key;
    
    root = merge(root->left, root->right);
    size--;
    
    return deletedNum;
}

//Calls the recursive print function
string maxHeap::printHeap() {
    
    stringstream ss;
    
    ss << toString(root, "        ");
    
    return ss.str();
}

//Merges two heaps together, puts larger values at the top
//This does the work for both deletion and insertion
//Swaps the children of every parent it touches
Node * maxHeap::merge(Node * r1, Node * r2) {
    
    Node * big;
    
    if (!r1) {return r2;}
    if (!r2) {return r1;}
    
    if (r1->key > r2->key) {
        r1->right = merge(r1->right, r2);
        big = r1;
    }
    else {
        r2->right = merge(r2->right, r1);
        big = r2;
    }
    
    numMerges++;
    swapKids(big);
    
    return big;
}

//Swaps the left and right child of a node
void maxHeap::swapKids(Node * parent) {
    
    Node * toSwap = parent->left;
    parent->left = parent->right;
    parent->right = toSwap;
    
    return;
}

//Recursively prints the heap
string maxHeap::toString(Node * subRoot, string indent) {
    
    stringstream ss;
    if (!subRoot) {return ss.str();}
    
    ss << toString(subRoot->right, indent + "        ");
    ss << indent << "[" << subRoot->key << "]" << endl;
    ss << toString(subRoot->left, indent + "        ");
    
    return ss.str();
}

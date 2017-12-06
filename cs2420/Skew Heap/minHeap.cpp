//
//  minHeap.cpp
//  Skew Heap
//
//  Created by Steven Proctor on 11/3/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "minHeap.hpp"

//Constructor
minHeap::minHeap() {
    numMerges = 0;
    root = NULL;
    size = 0;
}

//Destructor
minHeap::~minHeap() {
    
}

//Create new node, merge into heap
//Returns the inserted value for debug purposes
int minHeap::insert(int newVal) {
    
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
int minHeap::deleteMin() {
    
    if (!root) {return -1;}
    
    int deletedNum = root->key;
    
    root = merge(root->left, root->right);
    size--;
    
    return deletedNum;
}

//Calls the recursive print function
string minHeap::printHeap() {
    
    stringstream ss;
    
    ss << toString(root, "        ");
    
    return ss.str();
}

//Merges two heaps together, puts smaller values at the top
//This does the work for both deletion and insertion
//Swaps the children of every parent it touches
Node * minHeap::merge(Node * r1, Node * r2) {
    
    Node * small;
    
    if (!r1) {return r2;}
    if (!r2) {return r1;}
    
    if (r1->key < r2->key) {
        r1->right = merge(r1->right, r2);
        small = r1;
    }
    else {
        r2->right = merge(r2->right, r1);
        small = r2;
    }
    
    numMerges++;
    swapKids(small);
    
    return small;
}

//Swaps the left and right child of a node
void minHeap::swapKids(Node * parent) {
    
    Node * toSwap = parent->left;
    parent->left = parent->right;
    parent->right = toSwap;
    
    return;
}

//Recursively prints the heap
string minHeap::toString(Node * subRoot, string indent) {
    
    stringstream ss;
    if (!subRoot) {return ss.str();}
    
    ss << toString(subRoot->right, indent + "        ");
    ss << indent << "[" << subRoot->key << "]" << endl;
    ss << toString(subRoot->left, indent + "        ");
    
    return ss.str();
}
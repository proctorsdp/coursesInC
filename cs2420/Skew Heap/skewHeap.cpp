//
//  skewHeap.cpp
//  Skew Heap
//
//  Created by Steven Proctor on 11/3/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "skewHeap.hpp"
#include <sstream>

//constructor
skewHeap::skewHeap() {
    median = NULL;
}

//destructor
skewHeap::~skewHeap() {
    
}

//inserts new value into median heap
//if new value is bigger than median -> insert into minHeap
//if new value is smaller than median -> insert into maxHeap
//if median heap is too heavy on one side, rebalances heap
//sets children of median
void skewHeap::insert(int newVal) {
    
    if (!median) {
        median = new Node;
        median->key = newVal;
        return;
    }
    
    if (newVal > median->key) {
        min.insert(newVal);
    }
    else {
        max.insert(newVal);
    }
    
    if (min.getSize() - max.getSize() > 1) {
        max.insert(median->key);
        median->key = min.deleteMin();
    }
    else if (max.getSize() - min.getSize() > 1) {
        min.insert(median->key);
        median->key = max.deleteMax();
    }
    
    median->right = min.getMin();
    median->left = max.getMax();
}

//prints report of heap to the command window
//if boolean is true, print results the contents of heap
string skewHeap::report(bool printHeap) {
    stringstream ss;
    
    ss << "HEAP STATUS REPORT:\n";
    ss << "*************************\n";
    ss << "Current Median: " << median->key << endl;
    ss << "Total Heap Size: " << getSize() << endl;
    ss << "Size of Min Heap: " << min.getSize() << endl;
    ss << "Size of Max Heap: " << max.getSize() << endl;
    ss << "Merges in Min Heap: " << min.getMerges() << endl;
    ss << "Merges in Max Heap: " << max.getMerges() << endl;
    
    if (printHeap) {
        ss << endl << "CURRENT HEAP:\n" << endl;
        ss << min.printHeap();
        ss << "[" << median->key << "]" << endl;
        ss << max.printHeap();
        ss << endl << "END CURRENT HEAP\n" << endl;
    }
    
    ss << endl;
    return ss.str();
}

//returns size of median heap
int skewHeap::getSize() {
    return min.getSize() + max.getSize() + 1;
}
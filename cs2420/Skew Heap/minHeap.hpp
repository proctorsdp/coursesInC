//
//  minHeap.hpp
//  Skew Heap
//
//  Created by Steven Proctor on 11/3/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef minHeap_hpp
#define minHeap_hpp

#include <stdio.h>
#include <vector>
#include <sstream>
#include "node.h"

using namespace std;

class minHeap {
private:
    Node * root;                            //root of heap
    int size;                               //number of elements in heap
    int numMerges;                          //number of merges currently executed by heap
    
    Node * merge(Node *, Node *);           //merges two heaps
    void swapKids(Node *);                  //swap the kids of a given node
    string toString(Node *, string);        //recursively print heap
    
public:
    minHeap();                              //constructor
    ~minHeap();                             //desturctor
    
    int insert(int);                        //inserts a new value, merges to maintain heap priority
    int deleteMin();                        //delets the root, merges the subtrees
    string printHeap();                     //prints the heap
    
    int getMinVal() {return root->key;}     //returns the smallest value in the heap
    Node * getMin() {return root;}          //returns the root of the heap
    int getSize() {return size;}            //returns the size of the heap
    int getMerges() {return numMerges;}     //returns the number of merges performed by the heap
    
};

#endif /* minHeap_hpp */

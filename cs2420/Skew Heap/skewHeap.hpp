//
//  skewHeap.hpp
//  Skew Heap
//
//  Created by Steven Proctor on 11/3/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef skewHeap_hpp
#define skewHeap_hpp

#include <stdio.h>
#include "minHeap.hpp"
#include "maxHeap.hpp"

using namespace std;

class skewHeap{
private:
    minHeap min;            //contains values greater than median
    maxHeap max;            //contains values smaller than median
    Node * median;          //contains median
    
public:
    skewHeap();             //constructor
    ~skewHeap();            //destructor
    
    void insert(int);       //insert element into heap
    string printHeap();     //print contents of heap
    string report(bool);    //print status report of heap
    int getSize();          //returns number of elements in heap
    
};

#endif /* skewHeap_hpp */

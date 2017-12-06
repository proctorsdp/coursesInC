//
//  main.cpp
//  Skew Heap
//
//  Created by Steven Proctor on 11/3/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <vector>
#include "skewHeap.hpp"

using namespace std;

int main() {
    
    //Create size of test case and seed random numbers
    const int TEST_SIZE = 15;
    srand(unsigned (time(0)));
    
    //Create priority heap with the median at the root
    skewHeap median;
    
    //Fill heap with random numbers
    for (int i = 0; i < TEST_SIZE; i++) {
        int num = rand() % 1000;
        median.insert(num);
    }
    
    //Print status of heap
    cout << median.report(true) << endl;
    
    int size = 32;
    
    //Fill heap with random numbers, print report after every 32 inserts
    for (int i = TEST_SIZE; i < 1028; i++) {
        int num = rand() % 1000;
        median.insert(num);
        if (i == size) {
            cout << median.report(false) << endl;
            size *= 2;
        }
    }
    
    //Print final report
    cout << median.report(false) << endl;
    
    return 0;
}

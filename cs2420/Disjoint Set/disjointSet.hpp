//
//  disjointSet.hpp
//  Disjoint Set
//
//  Created by Steven Proctor on 11/16/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef disjointSet_hpp
#define disjointSet_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Network {
public:
    Network(int);
    ~Network();
    
    bool unionH(int , int);
    int find(int);
    bool isConnected();
    string printNetwork();
    string printStatus();
    
private:
    vector<int> network;
    int numFinds;
    int numUnions;
    
    void resolveInput(int);
    
};

#endif /* disjointSet_hpp */

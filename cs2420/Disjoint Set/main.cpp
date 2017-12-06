//
//  main.cpp
//  Disjoint Set
//
//  Created by Steven Proctor on 11/16/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include "disjointSet.hpp"

using namespace std;

const int SIZE = 1000;

void inputData(Network &N) {
    int one, two;
    
    cout << N.printNetwork() << endl;
    cout << "One: ";
    cin >> one;
    cout << "Two: ";
    cin >> two;
    cout << endl;
    N.unionH(one, two);
}

int main(int argc, const char * argv[]) {
    
    srand(unsigned (time(0)));
    Network Group(SIZE);
    int daysPassed = 0;
    int increment = SIZE / 2;
    int printStatus = increment;
    bool debug = false;
    
    cout << "Network Size: " << SIZE << endl << endl;
    while (!Group.isConnected()) {
        if (debug) {inputData(Group);}
        else {Group.unionH(rand() % SIZE, rand() % SIZE);}
        daysPassed++;
        
        if (daysPassed == printStatus) {
            cout << "Number of days passed: " << daysPassed << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << Group.printStatus() << endl;
            printStatus += increment;
        }
    }
    
    cout << endl << endl;
    cout << "SUCCESS! Everyone is in the same group!" << endl;
    cout << "***************************************" << endl;
    cout << "Total Number of Days passed: " << daysPassed << endl;
    cout << Group.printStatus() << endl;
    cout << Group.printNetwork() << endl;
    
    return 0;
}

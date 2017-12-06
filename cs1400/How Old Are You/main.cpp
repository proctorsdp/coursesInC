//
//  main.cpp
//  How Old Are You - Steven Proctor
//
//  Created by Steven Proctor on 1/25/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
  
    int age;
    
    cout << "What are you allowed to do?" << endl << endl;
    
    cout << "Enter your age: ";
    
    cin >> age;
    
    if (age < 16 ) {
        cout << endl << "You can't drive.\n";
    }
    
    else if ( age < 18 ) {
        cout << endl << "You can drive but not vote.\n";
    }
    
    else if ( age < 25 ) {
        cout << endl <<  "You can vote but not rent a car.\n";
    }
    
    else {
        cout << endl << "You can do pretty much anything.\n";
    }
    
    return 0;
}

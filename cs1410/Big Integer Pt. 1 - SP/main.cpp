//
//  main.cpp
//  Big Integer Part 1
//
//  Created by Steven Proctor on 2/8/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include<iostream>
#include"BigInteger.h"

using namespace std;

int main() {
    
    // Task 4. Compute 999!
    BigInteger answer(1);
    
    for (int i = 1; i <= 999; i++) {
        answer = multiply(answer, i);
    }
    
    cout << answer << endl;
    
    return 0;
}

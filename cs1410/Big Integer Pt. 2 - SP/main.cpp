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
    
    // Task Compute 999!
    BigInteger answer(1);       //Begin with number 1;
    
    for (int i = 1; i <= 999; i++) {
        answer = multiply(answer, i);   //Increment by 1, times by itself
    }
    
    cout << "999!= " << endl << "------" << endl << answer << endl << endl << endl;       //Print result
    cout << endl;
    
    
    
    // Task Compute 1000th Fibonacci Number
    BigInteger x, y, z;
    x = 0;                  //Create first two terms of sequence
    y = 1;
    
    int end = (1000 - 1)/3;     //Number of times needed to run the loop
    
    for (int i = 0; i < end; i++) {         //Add the previous two terms to find the third term, Repeated to 1000th term
        z = x + y;
        x = y + z;
        y = z + x;
    }
    
    cout << "The 1000th number in the Fibonacci Sequence is: " << endl;         //Print results
    cout << "-----------------------------------------------" << endl << y << endl << endl << endl;
    cout << endl;
    
    
    
    
    // Task Compute Exponents
    BigInteger a, b, c, d, temp;        //Create needed arrays
    
    int num = (1000/2) - 1;             //Times to run loop
   
    a = 2 * 2;
    for (int i = 1; i <= num; i++) {        //Compute 2^1000
        temp = multiply(a, 2);
        a = multiply(temp, 2);
    }
    
    b = 2 * 2 * 2;
    for (int i = 1; i <= num; i++) {        //Compute 2^1001
        temp = multiply(b, 2);
        b = multiply(temp, 2);
    }
    
    c = 2 * 2 * 2;
    num = (2000/2) - 1;
    for (int i = 1; i <= num; i++) {        //Compute 2^2001
        temp = multiply(c, 2);
        c = multiply(temp, 2);
    }
    
    d = a * b;      //Multiply 2^1000 and 2^1001
    
            //print results
    cout << "2^1000: " << endl << "-------" << endl << a << endl << endl << endl;
    cout << "2^1001: " << endl << "-------" << endl << b << endl << endl << endl;
    cout << "2^2001: " << endl << "-------" << endl << c << endl << endl << endl;
    cout << "2^1001 * 2^1000: " << endl << "----------------" << endl << d << endl << endl << endl;
    cout << endl;
    
    
    
    
    
    // Task Compare Exponents
    cout << "Is (2^1000 < 2^1001), True or False?" << endl;     //Compare 2^1000 to 2^1001
    if (a < b) {
        cout << ">True" << endl;
    }
    else {
        cout << ">False" << endl;
    }
    cout << endl;
    
    
    cout << "Is (2^1000 * 2^1001 = 2^2001), True or False?" << endl;    //Compare (2^1000 * 2^1001) to 2^2001
    if (d == c) {
        cout << ">True" << endl;
    }
    else {
        cout << ">False" << endl;
    }
    cout << endl;
    
    
    
    return 0;
}

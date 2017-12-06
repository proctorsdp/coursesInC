//
//  main.cpp
//  Calculator - Steven Proctor
//
//  Created by Steven Proctor on 3/2/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

void addition(double &, double &);
void subtraction(double &, double &);
void multiplier(double &, double &);
void division(double &, double &);
void exponents(double &, double &);
void modulusdivision(double &, double &);
void equality(double &, double &);
void lessthan(double &, double &);
void greaterthan(double &, double &);
void randomnumber(double &, double &);


int main() {
    
    double number1, number2;
    char math;
    
    cout << "The Calculator!" << endl;
    cout << "Valid operators: '+', '-', '*', '/', '^', '%', '=', '<', '>', '?'" << endl;
    cout << "To quit, press 0 and hit return.\n" << endl;
    
    cin >> number1;
    while (number1 != 0) {
        cin >> math;
        cin >> number2;
        
        switch (math) {
            case '+': addition(number1, number2);
                break;
            case '-': subtraction(number1, number2);
                break;
            case '*': multiplier(number1, number2);
                break;
            case '/': division(number1, number2);
                break;
            case '^': exponents(number1, number2);
                break;
            case '%': modulusdivision(number1, number2);
                break;
            case '=': equality(number1, number2);
                break;
            case '<': lessthan(number1, number2);
                break;
            case '>': greaterthan(number1, number2);
                break;
            case '?': randomnumber(number1, number2);
                break;
            default: cout << "Not a valid entry." << endl;
        }
        
        cout << endl;
        cin >> number1;
    }
    
    cout << "Goodbye!" << endl;
    
    return 0;
}

void addition(double & number1, double & number2) {
    cout << number1 + number2 << endl;
}

void subtraction(double & number1, double & number2) {
    cout << number1 - number2 << endl;
}

void multiplier(double & number1, double & number2) {
    cout << number1 * number2 << endl;
}

void division(double & number1, double & number2) {
    if (number2 == 0) {
        cout << "ERROR! You can't divide by zero." << endl;
    }
    else {
        cout << number1 / number2 << endl;
    }
}

void exponents(double & number1, double & number2) {
    cout << pow(number1, number2) << endl;
}

void modulusdivision(double & number1, double & number2) {
    cout << int(number1) % int(number2) << endl;
}

void equality(double & number1, double & number2) {
    if (number1 == number2) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
    }
}

void lessthan(double & number1, double & number2) {
    if (number1 < number2) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
    }
}

void greaterthan(double & number1, double & number2) {
    if (number1 > number2) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
    }
}

void randomnumber(double & number1, double & number2) {
    if (number1 < 1 || number2 < 1) {
        cout << "Error! You must enter a positive number for the '?' operator." << endl;
    }
    else {
        srand(number1);
        cout << rand() % int(number2) << endl;
    }
}